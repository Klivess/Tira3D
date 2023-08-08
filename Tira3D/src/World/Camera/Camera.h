#pragma once
#include "../World.h"
#include "../../vendor/glm/glm.hpp"
#include "../../Maths/TiraMath.h"
#include "../../Input/TiraInput.h"
#include "CameraRender.h"

class Camera
{
public:
	CameraRender cameraRender;
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
	Camera(WorldPosition position, WorldRotation rotation, float FOV, int* windowWidth, int* windowHeight, float sensitivity);
	~Camera();
	void SetMovementKeys(TiraKey forward,
		TiraKey backward,
		TiraKey right,
		TiraKey left,
		TiraKey up,
		TiraKey down);


	void LookAtObject(WorldPosition objectLoc);

	float GetFieldOfView();
	void SetFieldOfView(float FOV);
private:
	//This is a pointer to the current Tira3DRendering render class.
	float m_FieldOfView;
	float m_sensitivity;
};
