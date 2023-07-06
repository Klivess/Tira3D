#include "../Logger/Tira3DLogging.h"
#include <iostream>
#include <string>
#include "GL/glew.h"
#include "glfw3.h"

#pragma once
class Tira3D
{
private:
	void Window_FrameBuffer_Size_Callback(GLFWwindow* window, unsigned int width, unsigned int height);
public:
	static bool Initialize();
	static GLFWwindow* InstantiateWindow(int width, int height, const char* title, GLFWmonitor* monitor);
};

