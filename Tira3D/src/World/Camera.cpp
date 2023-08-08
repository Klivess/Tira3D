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

float Camera::GetFieldOfView()
{
	return FieldOfView;
}

void Camera::SetFieldOfView(float FOV)
{
	FieldOfView = FOV;
}
