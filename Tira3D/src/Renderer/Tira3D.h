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
#include <optional>
#include "Tira3DRendering.h"
#include "../World/Designer/TiraDesigner.h"

class Tira3D
{
public:
	Camera* AttachedCamera;

	Tira3DRendering renderThreadClass;
	std::thread renderThread;

	Tira3D();
	~Tira3D();
	bool UserClosedWindow;
	bool WindowIsCreated;

	void InstantiateWindow(int width, int height, const char* title, GLFWmonitor* monitor);
	void WaitUntilUserClosedWindow();
	TiraInput& Inputs();
	TiraDesigner& Designer();
	Camera& CreateCamera(WorldPosition position, WorldRotation rotation, float sensitivity = 0.1f, float FOV = 90);
private:
	TiraInput tiraInput;
	TiraDesigner designer;
};

