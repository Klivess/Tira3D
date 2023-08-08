#include "TiraMath.h"

glm::mat4 TiraMath::CreateTransformationMatrix()
{
	return glm::mat4(1.0);
}

glm::vec3 TiraMath::ConvertWorldPositionToVec3(WorldPosition position)
{
	return glm::vec3(position.x, position.y, position.z);
}

glm::vec3 TiraMath::ConvertWorldScaleToVec3(WorldScale scale)
{
	return glm::vec3(scale.x, scale.y, scale.z);
}

void TiraMath::RotateTransformX(glm::mat4& rotation, float degrees)
{
	RotateTransform(rotation, degrees, glm::vec3(1.0, 0.0, 0.0));
}

void TiraMath::RotateTransformY(glm::mat4& rotation, float degrees)
{
	RotateTransform(rotation, degrees, glm::vec3(0.0, 1.0, 0.0));
}

void TiraMath::RotateTransformZ(glm::mat4& rotation, float degrees)
{
	RotateTransform(rotation, degrees, glm::vec3(0.0, 0.0, 1.0));
}

void TiraMath::RotateTransform(glm::mat4& transform, float degrees, glm::vec3 axis)
{
	transform = glm::rotate(transform, glm::radians(degrees), axis);
}


