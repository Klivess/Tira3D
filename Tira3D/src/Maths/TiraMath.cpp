#include "TiraMath.h"

glm::mat4 TiraMath::CreateTransformationMatrix()
{
	return glm::mat4(1.0);
}

glm::vec3 TiraMath::ConvertWorldPositionToVec3(WorldPosition position)
{
	return glm::vec3(position.x, position.y, position.z);
}

glm::vec3 TiraMath::ConvertWorldRotationToVec3(WorldRotation rotation)
{
	return glm::vec3(rotation.x, rotation.y, rotation.z);
}

glm::vec3 TiraMath::ConvertWorldScaleToVec3(WorldScale scale)
{
	return glm::vec3(scale.x, scale.y, scale.z);
}

void TiraMath::RotateTransformX(glm::mat4& transform, float degrees)
{
	RotateTransform(transform, degrees, glm::vec3(1.0, 0.0, 0.0));
}

void TiraMath::RotateTransformY(glm::mat4& transform, float degrees)
{
	RotateTransform(transform, degrees, glm::vec3(0.0, 1.0, 0.0));
}

void TiraMath::RotateTransformZ(glm::mat4& transform, float degrees)
{
	RotateTransform(transform, degrees, glm::vec3(0.0, 0.0, 1.0));
}

void TiraMath::TranslateTransformX(glm::mat4& transform, float x)
{
	TranslateTransform(transform, glm::vec3(x, 0, 0));
}

void TiraMath::TranslateTransformY(glm::mat4& transform, float y)
{
	TranslateTransform(transform, glm::vec3(0, y, 0));
}

void TiraMath::TranslateTransformZ(glm::mat4& transform, float z)
{
	TranslateTransform(transform, glm::vec3(0, 0, z));
}

void TiraMath::ScaleTransformX(glm::mat4& transform, float x)
{
	ScaleTransform(transform, glm::vec3(x, 1, 1));
}

void TiraMath::ScaleTransformY(glm::mat4& transform, float y)
{
	ScaleTransform(transform, glm::vec3(1, y, 1));
}

void TiraMath::ScaleTransformZ(glm::mat4& transform, float z)
{
	ScaleTransform(transform, glm::vec3(1, 1, z));
}

void TiraMath::ScaleTransformByScalar(glm::mat4& transform, float scalar)
{
	ScaleTransform(transform, glm::vec3(scalar, scalar, scalar));
}

void TiraMath::TranslateWorldTransformToMatrixTransform(glm::mat4& transform, WorldTransform worldTransform)
{
	TranslateWorldPositionToMatrixTransform(transform, worldTransform.worldPosition);
	TranslateWorldRotationToMatrixTransform(transform, worldTransform.worldRotation);
	TranslateWorldScaleToMatrixTransform(transform, worldTransform.worldScale);
}

void TiraMath::TranslateWorldPositionToMatrixTransform(glm::mat4& transform, WorldPosition position)
{
	TranslateTransformX(transform, position.x);
	TranslateTransformY(transform, position.y);
	TranslateTransformZ(transform, position.z);
}

void TiraMath::TranslateWorldRotationToMatrixTransform(glm::mat4& transform, WorldRotation rotation)
{
	RotateTransformX(transform, rotation.x);
	RotateTransformY(transform, rotation.y);
	RotateTransformZ(transform, rotation.z);
}

void TiraMath::TranslateWorldScaleToMatrixTransform(glm::mat4& transform, WorldScale scale)
{
	ScaleTransformX(transform, scale.x);
	ScaleTransformY(transform, scale.y);
	ScaleTransformZ(transform, scale.z);
}

void TiraMath::RotateTransform(glm::mat4& transform, float degrees, glm::vec3 axis)
{
	transform = glm::rotate(transform, glm::radians(degrees), axis);
}

WorldPosition TiraMath::ConvertVec3ToWorldPosition(glm::vec3 position)
{
	return WorldPosition(position.x, position.y, position.z);
}

WorldRotation TiraMath::ConvertVec3ToWorldRotation(glm::vec3 rotation)
{
	return WorldRotation(rotation.x, rotation.y, rotation.z);
}

WorldScale TiraMath::ConvertVec3ToWorldScale(glm::vec3 scale)
{
	return WorldScale(scale.x, scale.y, scale.z);
}

void TiraMath::ScaleTransform(glm::mat4& transform, glm::vec3 scale)
{
	transform = glm::scale(transform, scale);
}

void TiraMath::TranslateTransform(glm::mat4& transform, glm::vec3 translation)
{
	transform = glm::translate(transform, translation);
}
