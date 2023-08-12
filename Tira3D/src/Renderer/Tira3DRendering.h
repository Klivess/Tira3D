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
#include "../WorldObjects/WorldObject.h"

class Tira3DRendering {
public:
	bool WindowInstantiated = false;
	bool* WindowClosed;
	GLFWwindow* currentWindow;
	int WindowHeight;
	int WindowWidth;
	Camera* currentCamera = nullptr;
	TiraInput* tiraInput = nullptr;
	std::vector<WorldObject> allWorldObj;

	WorldObject test1;
	WorldObject test2;

	WorldObject& CreateNewWorldObject(const std::string& objectName);
	Tira3DRendering();
	Camera* GetAttachedCamera();
	void CreateRender(int width, int height, const char* title, GLFWmonitor* monitor);
	void Clear();
	void Draw(WorldObject& obj);
private:
	// timing
	float deltaTime = 0.0f;	// time between current frame and last frame
	float lastFrame = 0.0f;

	std::vector<Shader> shaderCache;
	std::vector<Texture> textureCache;

	void ProcessInput(GLFWwindow* window);
	void MouseInput(GLFWwindow* window, double xpos, double ypos);

	Shader& GetCachedShader(std::string path);
	Texture& GetCachedTexture(std::string path);

	static void Window_FrameBuffer_Size_Callback(GLFWwindow* window, int width, int height);
	static void GLFWError_Callback(int error, const char* description);
	bool InitialiseRender();
};

