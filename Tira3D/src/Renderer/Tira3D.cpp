#include "Tira3D.h"
#include "GL/glew.h"

//Initialise Tira3D (GLFW) 
bool Tira3D::Initialize() {
	auto result = glfwInit();
	if (result == GLFW_FALSE) {
		Tira3DLogging::LogToConsole("Couldn't initialize GLFW.");
		return false;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	return true;
}

//Instantiate a window
//OpenGL is a state machine which only runs on one thread, do not try to multithread 3D rendering in one window!!!
GLFWwindow* Tira3D::InstantiateWindow(int width, int height, const char* title, GLFWmonitor* monitor) {
	GLFWwindow* window = glfwCreateWindow(width, height, title, monitor, NULL);
	if (window == NULL) {
		Tira3DLogging::LogToConsole("Failed to create GLFW window.");
		glfwTerminate();
		throw std::exception("Failed to create GLFW window.");
	}
	glfwMakeContextCurrent(window);
	return window;
}

//Whenever the current window gets resized.
//unsigned int used because negative values will throw error.
void Tira3D::Window_FrameBuffer_Size_Callback(GLFWwindow* window, unsigned int width, unsigned int height) {
	glViewport(0, 0, width, height);
}