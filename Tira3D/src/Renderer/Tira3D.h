#pragma once
#include "../vendor/stb_image.h" 
#define STB_IMAGE_IMPLEMENTATION
#include "../vendor/glew.h"
#include "../vendor/glfw3.h"
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
	Camera* AttachedCamera = nullptr;

	Tira3D();
	bool UserClosedWindow;

	void InstantiateWindow(int width, int height, const char* title, GLFWmonitor* monitor);
	void WaitUntilUserClosedWindow();

	Camera* CreateCamera(WorldPosition position, WorldRotation rotation, float FOV = 90);
private:

	Tira3DRendering renderThreadClass;
	std::thread renderThread;
};

