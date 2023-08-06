#include "Tira3DRendering.h"
#include <future>
#include <optional>
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

void Tira3DRendering::CreateRender(int width, int height, const char* title, GLFWmonitor* monitor) {
	InitialiseRender();
	Tira3DRendering::currentWindow = glfwCreateWindow(width, height, title, monitor, NULL);
	*WindowClosed = false;
	if (currentWindow == NULL) {
		glfwTerminate();
		throw std::exception("Failed to create GLFW window.");
	}
	glfwMakeContextCurrent(Tira3DRendering::currentWindow);
	glfwSwapInterval(1);
	glEnable(GL_MULTISAMPLE);
	//Initialise GLEW
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		throw ("Couldn't initialise GLEW: " + (const char)glewGetErrorString(err));
	}
	WindowInstantiated = true;
	glfwSetFramebufferSizeCallback(Tira3DRendering::currentWindow, Tira3DRendering::Window_FrameBuffer_Size_Callback);


	float vertices[] = {
		-0.5f, -0.5f, 0.0f, //0
		 0.5f, -0.5f, 0.0f, //1
		 0.0f,  0.5f, 0.0f, //2
		 1.0f,  1.0f, 0.0f, //3
		-1.0f,  1.0f, 0.0f, //4
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 4
	};

	VAO vao = CreateVAO();
	VertexBuffer vb = CreateVertexBuffer(vertices, sizeof(vertices));
	VertexBufferLayout vbLayout;
	vbLayout.Push<float>(3); //3 is amount of dimensions
	vao.AddBuffer(vb, vbLayout);
	IndexBuffer ib = CreateIndexBuffer(indices, std::size(indices));
	vao.Bind();
	ib.Bind();

	//Note by Klives: This is absolute, I know. This is a placeholder and if you are contributing to this project feel free to modify this.
	//Although the shader file is relative to this project, Tira3D Testing does not recognise Tira3D relative paths.
	Shader shader(R"(C:\Projects\Software\Tira3D\Tira3D\resources\shaders\Basic.kliveshader)");
	shader.Bind();
	//set colour
	shader.SetUniform4f("u_Color", 1.0, 0.0, 0.0, 1.0);

	while (!glfwWindowShouldClose(currentWindow))
	{
		glfwSwapBuffers(currentWindow);

		// Render here
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices));
		glfwPollEvents();
	}
	//When window/application closes
	*WindowClosed = true;
}