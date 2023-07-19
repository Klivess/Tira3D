#pragma once
#include "GL/glew.h"
#include "glfw3.h"
#include "../Logger/Tira3DLogging.h"
#include <iostream>
#include <string>
#include "Tira3DRendering.h"
#include <thread>
#include <vector>

//__debugbreak is compiler specific!!! will rewrite this in the future
//works on Visual Studio
#define ASSERT(x) if(!(x)) __debugbreak();

//wrap every single OpenGL reference/call in GLCall().
#define GLCall(x) GLClearError();\x;\ASSERT(GLLogCall(#x, __FILE__, __LINE__))
bool GLLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}


class Tira3D
{
public:
	bool UserClosedWindow;

	bool Initialize();
	void InstantiateWindow(int width, int height, const char* title, GLFWmonitor* monitor);
	void CreateTriangle();
	void WaitUntilUserClosedWindow();
private:
	Tira3DRendering renderThreadClass;
	std::thread renderThread;
};

