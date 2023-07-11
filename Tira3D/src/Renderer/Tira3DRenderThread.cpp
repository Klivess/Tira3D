#include "Tira3DRenderThread.h"
//GLFW Error Callback
void GLFWError_Callback(int error, const char* description) {
	Tira3DLogging::LogToConsole("GLFW Error: " + (std::string)description);
}

//Whenever the current window gets resized.
//unsigned int used because negative values will throw error.
void Window_FrameBuffer_Size_Callback(GLFWwindow* window, unsigned int width, unsigned int height) {
	glViewport(0, 0, width, height);
}

bool Tira3DRenderThread::InitialiseRender() {
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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwSetErrorCallback(GLFWError_Callback);
	return true;
}

void Tira3DRenderThread::DrawTriangle() {
	float positions[6] = {
		0.5f, 1.0f,
		-1.0f, -1.0f,
		1.0f, -1.0f
	};

	unsigned int buffer;
	glGenBuffers(1, &buffer);
 	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, std::size(positions) * sizeof(float), positions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, (std::size(positions) / 2), GL_FLOAT, GL_FALSE, (2 * sizeof(float)), 0);

	ShaderProgramSource source = Shader::ParseShader("C:\Projects\Software\Tira3D\Tira3D\resources\shaders\Basic.kliveshader");
	unsigned int shader = Shader::CreateShader(source.VertexSource, source.FragmentSource);
	AddShaderToProgram(shader);
}

void Tira3DRenderThread::AddShaderToProgram(unsigned int shader) {
	ShadersInUse.push_back(shader);
	glUseProgram(shader);
}

void Tira3DRenderThread::RemoveShaderFromProgram(unsigned int shader) {
	auto index = std::find(ShadersInUse.begin(), ShadersInUse.end(), shader);
	ShadersInUse.erase(index);
	glUseProgram(0);
}

void Tira3DRenderThread::CreateRender(int width, int height, const char *title, GLFWmonitor* monitor) {
	Tira3DRenderThread::currentWindow = glfwCreateWindow(width, height, title, monitor, NULL);
	if (currentWindow == NULL) {
		glfwTerminate();
		const char* error;
		throw std::exception("Failed to create GLFW window.");
	}
	glfwMakeContextCurrent(Tira3DRenderThread::currentWindow);
	//Initialise GLEW
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		throw ("Couldn't initialise GLEW: " + (const char)glewGetErrorString(err));
	}
	WindowInstantiated = true;
	float positions[6] = {
		0.5f, 1.0f,
		-1.0f, -1.0f,
		1.0f, -1.0f
	};

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, std::size(positions) * sizeof(float), positions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, (std::size(positions) / 2), GL_FLOAT, GL_FALSE, (2 * sizeof(float)), 0);

	ShaderProgramSource source = Shader::ParseShader(R"(resources\shaders\Basic.kliveshader)");
	unsigned int shader = Shader::CreateShader(source.VertexSource, source.FragmentSource);
	ShadersInUse.push_back(shader);
	cout << source.VertexSource << endl;
	glUseProgram(shader);
	//Render Loop
	while (!glfwWindowShouldClose(Tira3DRenderThread::currentWindow))
	{
		glfwSwapBuffers(Tira3DRenderThread::currentWindow);

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwPollEvents();
	}

	std::vector<unsigned int> tempVec = ShadersInUse;
	for (auto shader : tempVec) {
		RemoveShaderFromProgram(shader);
	}
}