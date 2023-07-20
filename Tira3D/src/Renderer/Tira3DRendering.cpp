#include "Tira3DRendering.h"
#include <future>
//GLFW Error Callback
void Tira3DRendering::GLFWError_Callback(int error, const char* description) {
	Tira3DLogging::LogToConsole("GLFW Error: " + (std::string)description);
}
//Whenever the current window gets resized.
//unsigned int used because negative values will throw error.
void Tira3DRendering::Window_FrameBuffer_Size_Callback(GLFWwindow* window, unsigned int width, unsigned int height) {
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
	//keep these window hints otherwise GLFW does not work
	//i don't care enough to need to know why this is needed
	GLCall(glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3));
	GLCall(glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3));
	GLCall(glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE));
	GLCall(glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE));
	GLCall(glfwSetErrorCallback(GLFWError_Callback));
	return true;
}
void Tira3DRendering::DrawTriangle() {
	float positions[6] = {
		0.5f, 1.0f,
		-1.0f, -1.0f,
		1.0f, -1.0f
	};

	VertexBuffer vb(positions);

	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, (std::size(positions) / 2), GL_FLOAT, GL_FALSE, (2 * sizeof(float)), 0));

	ShaderProgramSource source = Shader::ParseShader("C:\Projects\Software\Tira3D\Tira3D\resources\shaders\Basic.kliveshader");
	unsigned int shader = Shader::CreateShader(source.VertexSource, source.FragmentSource);
	AddShaderToProgram(shader);
}

void Tira3DRendering::AddShaderToProgram(unsigned int shader) {
	ShadersInUse.push_back(shader);
	GLCall(glUseProgram(shader));
}

void Tira3DRendering::RemoveShaderFromProgram(unsigned int shader) {
	auto index = std::find(ShadersInUse.begin(), ShadersInUse.end(), shader);
	ShadersInUse.erase(index);
	GLCall(glUseProgram(0));
}

void Tira3DRendering::CreateRender(int width, int height, const char *title, GLFWmonitor* monitor) {
	float positions[6] = {
	0.5f, 1.0f,
	-1.0f, -1.0f,
	1.0f, -1.0f
	};

	InitialiseRender();
	Tira3DRendering::currentWindow = glfwCreateWindow(width, height, title, monitor, NULL);
	*WindowClosed = false;
	if (currentWindow == NULL) {
		GLCall(glfwTerminate());
		throw std::exception("Failed to create GLFW window.");
	}
	GLCall(glfwMakeContextCurrent(Tira3DRendering::currentWindow));
	GLCall(glfwSwapInterval(1));
	//Initialise GLEW
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		throw ("Couldn't initialise GLEW: " + (const char)glewGetErrorString(err));
	}
	WindowInstantiated = true;
	while (!glfwWindowShouldClose(currentWindow))
	{
		GLCall(glfwSwapBuffers(currentWindow));

		/* Render here */
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));

		GLCall(glfwPollEvents());
	}
	//When window/application closes
	std::vector<unsigned int> tempVec = ShadersInUse;
	for (auto shader : tempVec) {
		RemoveShaderFromProgram(shader);
	}
	*WindowClosed = true;
}