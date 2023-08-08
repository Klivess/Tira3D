#pragma once
#include "../vendor/glew.h"
#include "../vendor/glfw3.h"
#include "../Logger/Tira3DLogging.h"
#include <iostream>
#include <string>
#include <thread>
#include "Shaders/Shader.h"
#include "RenderObjects/IndexBuffer.h"
#include "RenderObjects/VertexBuffer.h"
#include "RenderObjects/VAO.h"
#include "Textures/Texture.h"
#include "../World/Camera/Camera.h"

class Tira3DRendering {
public:
	bool WindowInstantiated = false;
	bool* WindowClosed;
	GLFWwindow* currentWindow;
	int WindowHeight;
	int WindowWidth;
	Camera* currentCamera = nullptr;

	Tira3DRendering();
	Camera* GetAttachedCamera();
	void CreateRender(int width, int height, const char* title, GLFWmonitor* monitor);
	void Clear();
	void Draw(const VAO& VAO, const Shader& shader) const;
private:
	// timing
	float deltaTime = 0.0f;	// time between current frame and last frame
	float lastFrame = 0.0f;
	bool firstMouse = true;
	float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	float pitch = 0.0f;
	float lastX = 800.0f / 2.0;
	float lastY = 600.0 / 2.0;

	void ProcessInput(GLFWwindow* window);
	void MouseInput(GLFWwindow* window, double xpos, double ypos);
	std::vector<unsigned int> shadersInUse = {};

	//Q: Is using std::vector a good idea to keep buffers in scope?
	//A: No. Not at all. This will cause disastrous performance issues as Tira3D scales, but it will do for now.
	std::vector<VertexBuffer> activeVertexBuffers;
	std::vector<IndexBuffer> activeIndexBuffer;
	std::vector<VAO> activeVAOs;

	// Function to add a new vertex buffer
	VertexBuffer& CreateVertexBuffer(const void* data, unsigned int size) {
		activeVertexBuffers.emplace_back(data, size);
		return activeVertexBuffers.back();
	}

	// Function to add a new VAO
	VAO& CreateVAO() {
		activeVAOs.emplace_back();
		return activeVAOs.back();
	}

	// Function to add a new VAO
	IndexBuffer& CreateIndexBuffer(const unsigned int* data, unsigned int count) {
		activeIndexBuffer.emplace_back(data, count);
		return activeIndexBuffer.back();
	}

	static void Window_FrameBuffer_Size_Callback(GLFWwindow* window, int width, int height);
	static void GLFWError_Callback(int error, const char* description);
	bool InitialiseRender();
};

