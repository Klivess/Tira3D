#include "WorldObject.h"

void WorldObject::InstantiateObject(WorldPosition worldPos) {
	currentWorldTransform.position = worldPos;
	currentWorldTransform.scale.CreateWorldScale(1, 1, 1);
}

void WorldObject::InstantiateObject(WorldTransform worldTransform)
{
	currentWorldTransform = worldTransform;

}
