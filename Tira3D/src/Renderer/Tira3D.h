#pragma once
#include "../vendor/stb_image.h" 
#define STB_IMAGE_IMPLEMENTATION
#include "../vendor/glew.h"
#include "../vendor/glfw3.h"
#include "../Logger/Tira3DLogging.h"
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include "../WorldObjects/WorldObject.h"
#include <optional>

class Tira3D
{
public:
	Camera* AttachedCamera;

	Tira3D();
	~Tira3D();
	bool UserClosedWindow;
	bool WindowIsCreated;

	void InstantiateWindow(int width, int height, const char* title, GLFWmonitor* monitor);
	void WaitUntilUserClosedWindow();

	TiraInput& Inputs();

	Camera& CreateCamera(WorldPosition position, WorldRotation rotation, float sensitivity = 0.1f, float FOV = 90);

	Tira3DRendering renderThreadClass;
	std::thread renderThread;
private:
	TiraInput tiraInput;
};

