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
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	auto pos = TiraMath::ConvertWorldPositionToVec3(GetAttachedCamera().transform.worldPosition);
	const float cameraSpeed = 0.05f; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		GetAttachedCamera().transform.worldPosition = TiraMath::ConvertVec3ToWorldPosition(pos = pos + (cameraSpeed * cameraFront));
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		GetAttachedCamera().transform.worldPosition = TiraMath::ConvertVec3ToWorldPosition(pos = pos - (cameraSpeed * cameraFront));
}

Camera& Tira3DRendering::GetAttachedCamera()
{
	return  &(tira3DAttachedCamera);
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
	GLCall(glEnable(GL_MULTISAMPLE));
	GLCall(glEnable(GL_BLEND));
	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	//Initialise GLEW
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		throw ("Couldn't initialise GLEW: " + (const char)glewGetErrorString(err));
	}
	WindowInstantiated = true;
	glfwSetFramebufferSizeCallback(Tira3DRendering::currentWindow, Window_FrameBuffer_Size_Callback);


	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	VAO vao = CreateVAO();
	VertexBuffer vb = CreateVertexBuffer(vertices, sizeof(vertices));
	VertexBufferLayout vbLayout;
	//vertices layout
	vbLayout.Push<float>(3);
	//texture layout
	vbLayout.Push<float>(2);
	vao.AddBuffer(vb, vbLayout);
	vao.Bind();

	//Note by Klives: This is absolute, I know. This is a placeholder and if you are contributing to this project feel free to modify this.
	//Although the shader file is relative to this project, Tira3D Testing does not recognise Tira3D relative paths.
	Shader shader(R"(C:\Projects\Software\Tira3D\Tira3D\resources\shaders\Basic.kliveshader)");
	shader.Bind();

	Texture tex(R"(C:\Projects\Software\Tira3D\Tira3D\resources\textures\TestTex3.jpg)");
	tex.Bind();
	shader.SetUniform1i("u_Texture", 0);

	glm::mat4 transform = TiraMath::CreateTransformationMatrix();
	glm::mat4 model = TiraMath::CreateTransformationMatrix();
	glm::mat4 view = TiraMath::CreateTransformationMatrix();
	GetAttachedCamera().transform.worldPosition = WorldPosition(0, 0, -5);

	while (!glfwWindowShouldClose(currentWindow))
	{
		glfwSwapBuffers(currentWindow);

		ProcessInput(currentWindow);

		// Render here
		Clear();
		Draw(vao, shader);
		TiraMath::RotateTransformX(model, -0.2);
		TiraMath::RotateTransformY(model, -0.2);
		TiraMath::RotateTransformZ(model, -0.2);
		glm::mat4 proj = glm::perspective(glm::radians(GetAttachedCamera().GetFieldOfView()), (float)WindowWidth / (float)WindowHeight, 0.1f, 100.0f);
		view = glm::translate(view, TiraMath::ConvertWorldPositionToVec3(GetAttachedCamera().transform.worldPosition));

		///camera.transform.worldPosition.MoveRight(0.01);
		shader.SetModelViewProjection(model, view, proj);

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

void Tira3DRendering::Draw(const VAO& vao, const Shader& shader) const
{
	shader.Bind();
	vao.Bind();
	GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
}
