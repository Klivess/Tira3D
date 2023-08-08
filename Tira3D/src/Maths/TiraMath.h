#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"
#include "../vendor/glm/gtc/type_ptr.hpp"
#include "../World/World.h"

#pragma once
class TiraMath
{
public:
	static glm::mat4 CreateTransformationMatrix();

	static glm::vec3 ConvertWorldPositionToVec3(WorldPosition position);
	static glm::vec3 ConvertWorldRotationToVec3(WorldRotation rotation);
	static glm::vec3 ConvertWorldScaleToVec3(WorldScale scale);
	static WorldPosition ConvertVec3ToWorldPosition(glm::vec3 position);
	static WorldPosition ConvertVec3ToWorldRotation(glm::vec3 rotation);
	static WorldScale ConvertVec3ToWorldScale(glm::vec3 scale);

	static void RotateTransformX(glm::mat4& transform, float degrees);
	static void RotateTransformY(glm::mat4& transform, float degrees);
	static void RotateTransformZ(glm::mat4& transform, float degrees);

	static void TranslateTransformX(glm::mat4& transform, float x);
	static void TranslateTransformY(glm::mat4& transform, float y);
	static void TranslateTransformZ(glm::mat4& transform, float z);

	static void ScaleTransformX(glm::mat4& transform, float x);
	static void ScaleTransformY(glm::mat4& transform, float y);
	static void ScaleTransformZ(glm::mat4& transform, float z);
	static void ScaleTransformByScalar(glm::mat4& transform, float scalar);
private:
	static void RotateTransform(glm::mat4& transform, float degrees, glm::vec3 axis);
	static void TranslateTransform(glm::mat4& transform, glm::vec3 translation);
	static void ScaleTransform(glm::mat4& transform, glm::vec3 scale);
};

