#pragma once
#include "../World/World.h"

class BasicMovementSystem
{
public:
	BasicMovementSystem() {}
	BasicMovementSystem(WorldTransform* transformToModify, WorldRotation* frontDirection, float speed = 10);

	void SetMovementSpeed(float speed);

	void MoveForward();
	void MoveRight();
	void MoveLeft();
	void MoveBack();

	void MoveUp();
	void MoveDown();

private:
	float MovementSpeed;

	WorldTransform* transformToModify;
	WorldRotation* frontDirection;
};

