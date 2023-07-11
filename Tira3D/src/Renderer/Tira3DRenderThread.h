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

	bool InitialiseRender();
	void CreateRender(int width, int height, const char* title, GLFWmonitor* monitor);
	void DrawTriangle();
private:
	vector<unsigned int> ShadersInUse = {};
	GLFWwindow* currentWindow;

	void AddShaderToProgram(unsigned int shader);
	void RemoveShaderFromProgram(unsigned int shader);
};

