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
	static glm::vec3 ConvertWorldScaleToVec3(WorldScale scale);

	static void RotateTransformX(glm::mat4& rotation, float degrees);
	static void RotateTransformY(glm::mat4& rotation, float degrees);
	static void RotateTransformZ(glm::mat4& rotation, float degrees);
private:
	static void RotateTransform(glm::mat4& transform, float degrees, glm::vec3 axis);
};

