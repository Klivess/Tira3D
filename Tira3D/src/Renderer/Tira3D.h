#pragma once
#include "GL/glew.h"
#include "glfw3.h"
#include "../Logger/Tira3DLogging.h"
#include <iostream>
#include <string>
#include "Tira3DRendering.h"
#include <thread>
#include <vector>
#include "../WorldObjects/WorldObject.h"

class Tira3D
{
public:
	bool UserClosedWindow;

	bool Initialize();
	void InstantiateWindow(int width, int height, const char* title, GLFWmonitor* monitor);
	void CreateTriangle();
	void WaitUntilUserClosedWindow();

	WorldObject CreateWorldObject(TiraObjects object, WorldPosition position, WorldScale scale);
private:
	Tira3DRendering renderThreadClass;
	std::thread renderThread;
};

