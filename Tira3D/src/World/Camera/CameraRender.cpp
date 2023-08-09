#include "CameraRender.h"

CameraRender::CameraRender()
{
}

CameraRender::CameraRender(WorldTransform* cameraTransformRef, float* FieldOfView, int* windowWidth, int* windowHeight, float* sensitivity)
{
	cameraTransform = cameraTransformRef;
	cameraFOV = FieldOfView;
	this->windowHeight = windowHeight;
	this->windowWidth = windowWidth;
	this->sensitivity = sensitivity;
}

CameraRender::~CameraRender()
{
	//delete cameraTransform;
}

glm::mat4 CameraRender::CalculateProjectionMatrix()
{
	float fov = *cameraFOV;
	glm::mat4 proj = glm::perspective(glm::radians(fov), (float)*windowWidth / (float)*windowHeight, 0.1f, 100.0f);
	return proj;
}

glm::mat4 CameraRender::CalculateViewMatrix()
{
	auto pos = TiraMath::ConvertWorldPositionToVec3(cameraTransform->worldPosition);
	glm::mat4 view = glm::lookAt(pos, pos + TiraMath::ConvertWorldRotationToVec3(cameraFront), cameraUp);
	return view;
}

void CameraRender::CameraMouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	float lastX = *windowWidth / 2;
	float lastY = *windowHeight / 2;

	float yaw = -90;
	float pitch = 0.0f;


	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
	lastX = xpos;
	lastY = ypos;

	xoffset *= *sensitivity;
	yoffset *= *sensitivity;

	//yaw
	yaw += xoffset;
	//pitch
	pitch += yoffset;

	//Clamp camera to not make weird camera movements.
	const float clampLimitAbove = 89.0f;
	const float clampLimitBelow = -89.0f;
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = TiraMath::ConvertVec3ToWorldRotation(glm::normalize(front));


}
