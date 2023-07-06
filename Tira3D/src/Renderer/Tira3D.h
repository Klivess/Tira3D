#include "GL/glew.h"
#include "glfw3.h"
#include "../Logger/Tira3DLogging.h"
#include <iostream>
#include <string>

#pragma once
class Tira3D
{
private:
	void Window_FrameBuffer_Size_Callback(GLFWwindow* window, int width, int height);
public:
	static bool Initialize();
	static GLFWwindow* InstantiateWindow(int width, int height, const char* title, GLFWmonitor* monitor);
};

