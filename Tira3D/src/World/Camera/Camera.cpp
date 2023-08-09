#include "Camera.h"
Camera::Camera(WorldPosition position, WorldRotation rotation, float FOV, int* windowWidth, int* windowHeight, float sensitivity)
{
	transform = WorldTransform(position, rotation, WorldScale(1, 1, 1));
	m_sensitivity = sensitivity;
	SetFieldOfView(FOV);
	cameraRender = CameraRender(&transform, &m_FieldOfView, windowWidth, windowHeight, &m_sensitivity);
	m_Movement = BasicMovementSystem(&transform, &cameraRender.cameraFront);
}

Camera::~Camera()
{
}

void Camera::LookAtObject(WorldPosition objectLoc)
{
	//unfinished
	auto pos = TiraMath::ConvertWorldPositionToVec3(transform.worldPosition);
}

BasicMovementSystem& Camera::BasicMovement()
{
	return m_Movement;
}

float Camera::GetFieldOfView()
{
	return m_FieldOfView;
}

void Camera::SetFieldOfView(float FOV)
{
	m_FieldOfView = FOV;
}
