#pragma once
#include "../World.h"
#include "../../vendor/glm/glm.hpp"
#include "../../Maths/TiraMath.h"
#include "../../Input/TiraInput.h"
class CameraRender {
public:
	CameraRender();
	CameraRender(WorldTransform* cameraTransformRef, float* FieldOfView, int* windowWidth, int* windowHeight, float* sensitivity);
	~CameraRender();

	glm::mat4 CalculateProjectionMatrix();
	glm::mat4 CalculateViewMatrix();

	void CameraMouseCallback(GLFWwindow* window, double xpos, double ypos);

	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

private:
	WorldTransform* cameraTransform;
	float* cameraFOV;
	int* windowWidth;
	int* windowHeight;
	float* sensitivity;
};