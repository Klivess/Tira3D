#include "BasicMovement.h"
#include "../Maths/TiraMath.h"

BasicMovementSystem::BasicMovementSystem(WorldTransform* transformToModify, WorldRotation* frontDirection, float speed)
{
	this->transformToModify = transformToModify;
	this->frontDirection = frontDirection;
	SetMovementSpeed(speed);
}

void BasicMovementSystem::SetMovementSpeed(float speed)
{
	MovementSpeed = speed;
}

void BasicMovementSystem::MoveForward()
{
	auto pos = TiraMath::ConvertWorldPositionToVec3((*transformToModify).worldPosition);
	auto& transform = (*transformToModify);
	auto& frontDir = (*frontDirection);
	transform.worldPosition = TiraMath::ConvertVec3ToWorldPosition(pos = pos + (MovementSpeed
		* TiraMath::ConvertWorldRotationToVec3(frontDir)));

}

void BasicMovementSystem::MoveRight()
{
	auto pos = TiraMath::ConvertWorldPositionToVec3((*transformToModify).worldPosition);
	auto& transform = (*transformToModify);
	auto& frontDir = (*frontDirection);
	transform.worldPosition = TiraMath::ConvertVec3ToWorldPosition(pos += glm::normalize(glm::cross(TiraMath::ConvertWorldRotationToVec3(frontDir), cameraUp)) * MovementSpeed);
}

void BasicMovementSystem::MoveLeft()
{
	auto pos = TiraMath::ConvertWorldPositionToVec3((*transformToModify).worldPosition);
	auto& transform = (*transformToModify);
	auto& frontDir = *frontDirection;
	transform.worldPosition = TiraMath::ConvertVec3ToWorldPosition(pos -= glm::normalize(glm::cross(TiraMath::ConvertWorldRotationToVec3(frontDir), cameraUp)) * MovementSpeed);

}

void BasicMovementSystem::MoveBack()
{
	auto pos = TiraMath::ConvertWorldPositionToVec3((*transformToModify).worldPosition);
	auto& transform = (*transformToModify);
	auto& frontDir = (*frontDirection);
	transform.worldPosition = TiraMath::ConvertVec3ToWorldPosition(pos = pos - (MovementSpeed * TiraMath::ConvertWorldRotationToVec3(frontDir)));
}

void BasicMovementSystem::MoveUp()
{
	auto pos = TiraMath::ConvertWorldPositionToVec3((*transformToModify).worldPosition);
	auto& transform = (*transformToModify);
	auto& frontDir = (*frontDirection);

	transform.worldPosition = TiraMath::ConvertVec3ToWorldPosition(pos = pos + (MovementSpeed * cameraUp));
}

void BasicMovementSystem::MoveDown()
{
	auto pos = TiraMath::ConvertWorldPositionToVec3((*transformToModify).worldPosition);
	auto& transform = (*transformToModify);
	auto& frontDir = (*frontDirection);

	transform.worldPosition = TiraMath::ConvertVec3ToWorldPosition(pos = pos - (MovementSpeed * cameraUp));
}
