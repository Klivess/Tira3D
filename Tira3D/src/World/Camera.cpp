#include "Camera.h"

Camera::Camera()
{
	Camera::Camera(WorldPosition(0, 0, 0), WorldRotation(0, 0, 0));
}

Camera::Camera(WorldPosition position, WorldRotation rotation, float FOV)
{
	transform = WorldTransform(position, rotation, WorldScale(1, 1, 1));
	SetFieldOfView(FOV);
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

float Camera::GetFieldOfView()
{
	return FieldOfView;
}

void Camera::SetFieldOfView(float FOV)
{
	FieldOfView = FOV;
}
