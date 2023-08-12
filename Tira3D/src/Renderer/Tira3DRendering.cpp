#include "Tira3DRendering.h"
#include "Tira3D.h"
#include <future>
#include <optional>
#include <math.h>
#include "../Maths/TiraMath.h"

//GLFW Error Callback
void Tira3DRendering::GLFWError_Callback(int error, const char* description) {
	Tira3DLogging::LogToConsole("GLFW Error: " + (std::string)description);
}
//Whenever the current window gets resized.
//unsigned int used because negative values will throw error.
void Tira3DRendering::Window_FrameBuffer_Size_Callback(GLFWwindow* window, int width, int height) {
	GLCall(glViewport(0, 0, width, height));
}

bool Tira3DRendering::InitialiseRender() {
	//Initialise GLFW
	auto result = glfwInit();
	if (result == GLFW_FALSE) {
		Tira3DLogging::LogToConsole("Couldn't initialize GLFW.");
		return false;
	}
	else if (result == GLFW_TRUE) {
		std::string str = "GLFW is initialised. Version: " + (std::string)glfwGetVersionString();
		Tira3DLogging::LogToConsole(str);
	}
	glfwSetErrorCallback(GLFWError_Callback);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	return true;
}

/*
void Tira3DRendering::AddShaderToProgram(unsigned int shader) {
	shadersInUse.push_back(shader);
	GLCall(glUseProgram(shader));
}

void Tira3DRendering::RemoveShaderFromProgram(unsigned int shader) {
	auto index = std::find(shadersInUse.begin(), shadersInUse.end(), shader);
	shadersInUse.erase(index);
	GLCall(glUseProgram(0));
}
*/

Tira3DRendering::Tira3DRendering()
{
}

void Tira3DRendering::ProcessInput(GLFWwindow* window)
{
	auto& existingInputs = tiraInput->GetExistingInputs();

	if (existingInputs.empty() == false) {
		for (unsigned int i = 0; i < existingInputs.size(); i++) {
			auto& input = existingInputs[i];
			if (input.key == TIRA_KEY_SCROLL_UP || input.key == TIRA_KEY_SCROLL_DOWN)
				continue;
			if (glfwGetKey(window, input.key) == input.triggertype) {
				input.boundfunction();
			}
		}
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	Tira3DRendering* app = static_cast<Tira3DRendering*>(glfwGetWindowUserPointer(window));
	app->currentCamera->cameraRender.CameraMouseCallback(window, xpos, ypos);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Tira3DRendering* app = static_cast<Tira3DRendering*>(glfwGetWindowUserPointer(window));
	auto& existingInputs = app->tiraInput->GetExistingInputs();

	if (existingInputs.empty() == false) {
		for (unsigned int i = 0; i < existingInputs.size(); i++) {
			auto& input = existingInputs[i];
			if (input.key == TIRA_KEY_SCROLL_UP && yoffset > 0) {
				for (int i = 0; i < yoffset; i++)
				{
					input.boundfunction();
				}
			}
			else if (input.key == TIRA_KEY_SCROLL_DOWN && yoffset < 0) {
				for (int i = 0; i < abs(yoffset); i++)
				{
					input.boundfunction();
				}
			}
			if (glfwGetKey(window, input.key) == input.triggertype) {
				input.boundfunction();
			}
		}
	}
}


Camera* Tira3DRendering::GetAttachedCamera()
{
	if (currentCamera == nullptr) {
		return new Camera(WorldPosition(0, 0, 0), WorldRotation(0, 0, 0), 90, &WindowWidth, &WindowHeight, 0.1);
	}
	else {
		return currentCamera;
	}
}
void Tira3DRendering::CreateRender(int width, int height, const char* title, GLFWmonitor* monitor) {
	WindowHeight = height;
	WindowWidth = width;
	InitialiseRender();
	Tira3DRendering::currentWindow = glfwCreateWindow(width, height, title, monitor, NULL);
	*WindowClosed = false;
	if (currentWindow == NULL) {
		glfwTerminate();
		throw std::exception("Failed to create GLFW window.");
	}
	glfwMakeContextCurrent(Tira3DRendering::currentWindow);
	glfwSwapInterval(1);
	glfwSetInputMode(currentWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	GLCall(glEnable(GL_MULTISAMPLE));
	GLCall(glEnable(GL_BLEND));
	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	// Pass 'this' as user data to the callback
	glfwSetWindowUserPointer(currentWindow, this);
	//Initialise GLEW
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		throw ("Couldn't initialise GLEW: " + (const char)glewGetErrorString(err));
	}
	WindowInstantiated = true;
	glfwSetFramebufferSizeCallback(Tira3DRendering::currentWindow, Window_FrameBuffer_Size_Callback);

	//TiraMath::ScaleTransformZ(model, 10);

	while (!glfwWindowShouldClose(currentWindow))
	{
		auto currentcamera = GetAttachedCamera();

		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwSwapBuffers(currentWindow);

		ProcessInput(currentWindow);
		glfwSetCursorPosCallback(currentWindow, mouse_callback);
		glfwSetScrollCallback(currentWindow, scroll_callback);

		/*
		Tira3DLogging::LogToConsole("I am at x:" + std::to_string(currentcamera->transform.worldPosition.x)
			+ " y: " + std::to_string(currentcamera->transform.worldPosition.y)
			+ " z: " + std::to_string(currentcamera->transform.worldPosition.z));
			*/

			// Render here
		Clear();
		for (unsigned int i = 0; i < allWorldObj.size(); i++) {
			WorldObject& obj = allWorldObj[i];
			Draw(obj);
		}
		///camera.transform.worldPosition.MoveRight(0.01);

		glfwGetFramebufferSize(currentWindow, &WindowWidth, &WindowHeight);
		glfwPollEvents();
	}
	//When window/application closes
	*WindowClosed = true;
}

void Tira3DRendering::Clear()
{
	GLCall(glClearColor(0, 0.7, 0.7, 0.7));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}


Shader& Tira3DRendering::GetCachedShader(std::string path)
{
	auto it = std::find_if(shaderCache.begin(), shaderCache.end(),
		[path](const Shader& obj) {
			return obj.m_shaderFilepath == path;
		});
	if (it != shaderCache.end()) {
		return *it;
	}
	else {
		return shaderCache.emplace_back(path);
	}
}

Texture& Tira3DRendering::GetCachedTexture(std::string path)
{
	auto it = std::find_if(textureCache.begin(), textureCache.end(),
		[path](const Texture& obj) {
			return obj.m_FilePath == path;
		});
	if (it != textureCache.end()) {
		return *it;
	}
	else {
		return textureCache.emplace_back(path);
	}
}

void Tira3DRendering::Draw(WorldObject& obj)
{
	//matrices
	glm::mat4 proj = currentCamera->cameraRender.CalculateProjectionMatrix();
	glm::mat4 view = currentCamera->cameraRender.CalculateViewMatrix();
	glm::mat4 model = TiraMath::CreateTransformationMatrix();

	VAO vao = VAO();
	VertexBuffer vb = VertexBuffer(obj.GetMeshVerticies().data(), obj.GetMeshVerticies().size() * sizeof(obj.GetMeshVerticies()[0]));
	vao.AddBuffer(vb, obj.GetVBLayout());
	vao.Bind();

	Shader& shader = GetCachedShader(obj.GetShaderSource());
	shader.Bind();

	Texture& tex = GetCachedTexture(obj.GetTextureFile());
	tex.Bind();
	shader.SetUniform1i("u_Texture", 0);

	//Set WorldPosition
	TiraMath::TranslateWorldTransformToMatrixTransform(model, obj.currentWorldTransform);
	shader.SetModelViewProjection(model, view, proj);

	GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
	tex.Unbind();
}

WorldObject& Tira3DRendering::CreateNewWorldObject(const std::string& objectName)
{
	return allWorldObj.emplace_back(objectName);
}