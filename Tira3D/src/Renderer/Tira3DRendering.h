#pragma once
#include "GL/glew.h"
#include "glfw3.h"
#include "../Logger/Tira3DLogging.h"
#include <iostream>
#include <string>
#include <thread>
#include "Shaders/Shader.h"
#include "RenderObjects/IndexBuffer.h"
#include "RenderObjects/VertexBuffer.h"
#include "RenderObjects/VAO.h"

class Tira3DRendering {
public:
	bool WindowInstantiated = false;
	bool* WindowClosed;
	GLFWwindow* currentWindow;

	void CreateRender(int width, int height, const char* title, GLFWmonitor* monitor);
private:
	vector<unsigned int> shadersInUse = {};

	//Q: Is using std::vector a good idea to keep buffers in scope?
	//A: No. Not at all. This will cause disastrous performance issues as Tira3D scales, but it will do for now.
	vector<VertexBuffer> activeVertexBuffers;
	vector<IndexBuffer> activeIndexBuffer;
	vector<VAO> activeVAOs;

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
	void AddShaderToProgram(unsigned int shader);
	void RemoveShaderFromProgram(unsigned int shader);
};

