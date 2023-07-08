extern "C" {
#include "glad/glad.h";
}
#include "glfw3.h"
#include "../Logger/Tira3DLogging.h"
#include <iostream>
#include <string>



#pragma once
class Tira3D
{
private:
	GLFWwindow* currentWindow;

	void Window_FrameBuffer_Size_Callback(GLFWwindow* window, unsigned int width, unsigned int height);
public:
	bool Initialize();
	void InstantiateWindow(int width, int height, const char* title, GLFWmonitor* monitor);
};

