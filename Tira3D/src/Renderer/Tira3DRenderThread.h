#pragma once
#include "GL/glew.h"
#include "glfw3.h"
#include "../Logger/Tira3DLogging.h"
#include <iostream>
#include <string>
#include <thread>
#include "../Shaders/Shader.h"
#include <iterator>
#include <algorithm>

class Tira3DRenderThread {
public:
	bool WindowInstantiated = false;
	GLFWwindow* currentWindow;

	bool InitialiseRender();
	void CreateRender(int width, int height, const char* title, GLFWmonitor* monitor);
	void DrawTriangle();
	static void Window_FrameBuffer_Size_Callback(GLFWwindow* window, unsigned int width, unsigned int height);
	static void GLFWError_Callback(int error, const char* description);
private:
	vector<unsigned int> ShadersInUse = {};

	void AddShaderToProgram(unsigned int shader);
	void RemoveShaderFromProgram(unsigned int shader);
};

