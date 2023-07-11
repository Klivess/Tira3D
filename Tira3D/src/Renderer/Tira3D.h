#pragma once
#include "GL/glew.h"
#include "glfw3.h"
#include "../Logger/Tira3DLogging.h"
#include <iostream>
#include <string>
#include "Tira3DRenderThread.h"
#include <thread>
#include <vector>

class Tira3D
{
public:
	bool Initialize();
	void InstantiateWindow(int width, int height, const char* title, GLFWmonitor* monitor);
	void CreateTriangle();
private:
	Tira3DRenderThread renderThreadClass;
	std::thread renderThread;
};

