#include "Camera.h"
Camera::Camera(WorldPosition position, WorldRotation rotation, float FOV, int* windowWidth, int* windowHeight, float sensitivity)
{
	transform = WorldTransform(position, rotation, WorldScale(1, 1, 1));
	m_sensitivity = sensitivity;
	SetFieldOfView(FOV);
	cameraRender = CameraRender(&transform, &m_FieldOfView, windowWidth, windowHeight, &m_sensitivity);
}

Camera::~Camera()
{
}

void Camera::SetMovementKeys(TiraKey forward, TiraKey backward, TiraKey right, TiraKey left, TiraKey up, TiraKey down)
{
	CameraControlKeys.forward = forward;
	CameraControlKeys.backward = backward;
	CameraControlKeys.right = right;
	CameraControlKeys.left = left;
	CameraControlKeys.up = up;
	CameraControlKeys.down = down;
}

void Camera::LookAtObject(WorldPosition objectLoc)
{
	//unfinished
	auto pos = TiraMath::ConvertWorldPositionToVec3(transform.worldPosition);
}

float Camera::GetFieldOfView()
{
	return m_FieldOfView;
}

void Camera::SetFieldOfView(float FOV)
{
	m_FieldOfView = FOV;
}
