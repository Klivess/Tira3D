#pragma once
#include "../World.h"
#include "../../vendor/glm/glm.hpp"
#include "../../Maths/TiraMath.h"
#include "../../Input/TiraInput.h"
#include "CameraRender.h"
#include "../../Basics/BasicMovement.h"

class Camera
{
public:
	CameraRender cameraRender;
	WorldTransform transform;

	Camera();
	Camera(WorldPosition position, WorldRotation rotation, float FOV, int* windowWidth, int* windowHeight, float sensitivity);
	~Camera();

	void LookAtObject(WorldPosition objectLoc);

	BasicMovementSystem& BasicMovement();
	BasicMovementSystem m_Movement;

	float GetFieldOfView();
	void SetFieldOfView(float FOV);
private:
	//This is a pointer to the current Tira3DRendering render class.
	float m_FieldOfView;
	float m_sensitivity;
};
