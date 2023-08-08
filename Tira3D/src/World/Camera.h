#pragma once
#include "World.h"
#include "../vendor/glm/glm.hpp"
#include "../Maths/TiraMath.h"
#include "../Input/TiraInput.h"


class Camera
{
public:
	struct {
		TiraKey forward;
		TiraKey backward;
		TiraKey right;
		TiraKey left;
		TiraKey up;
		TiraKey down;
	} CameraControlKeys;
	WorldTransform transform;
	Camera();
	Camera(WorldPosition position, WorldRotation rotation, float FOV = 90);
	~Camera();

	void SetMovementKeys(TiraKey forward,
		TiraKey backward,
		TiraKey right,
		TiraKey left,
		TiraKey up,
		TiraKey down);

	float GetFieldOfView();
	void SetFieldOfView(float FOV);


private:
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 CalculateCameraTarget() {
		return TiraMath::ConvertWorldRotationToVec3(transform.worldRotation);
	}
	glm::vec3 CalculateCameraDirection() {
		return glm::normalize(TiraMath::ConvertWorldPositionToVec3(transform.worldPosition) - CalculateCameraTarget());
	}
	glm::vec3 CalculateCameraRight() {
		return glm::normalize(glm::cross(cameraUp, CalculateCameraDirection()));
	}

	float FieldOfView;
};

