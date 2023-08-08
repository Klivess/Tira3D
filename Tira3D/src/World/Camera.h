#pragma once
#include "World.h"
class Camera
{
public:
	WorldTransform transform;
	Camera();
	Camera(WorldPosition position, WorldRotation rotation, float FOV = 90);
	~Camera();
	float GetFieldOfView();
	void SetFieldOfView(float FOV);
private:
	float FieldOfView;
};

