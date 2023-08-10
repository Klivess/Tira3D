#include "WorldObject.h"

WorldObject::WorldObject()
{
}

void WorldObject::SetWorldPosition(WorldPosition position)
{
	currentWorldTransform.worldPosition = position;
}

void WorldObject::SetWorldRotation(WorldRotation rotation)
{
	currentWorldTransform.worldRotation = rotation;
}

void WorldObject::SetWorldScale(WorldScale scale)
{
	currentWorldTransform.worldScale = scale;
}

void WorldObject::SetWorldTransform(WorldTransform transform)
{
	currentWorldTransform = transform;
}

void WorldObject::InstantiateObject(WorldPosition worldPos)
{
	if (!ObjectInstantiated) {
		currentWorldTransform.worldPosition = worldPos;
		currentWorldTransform.worldRotation = WorldRotation(0, 0, 0);
		currentWorldTransform.worldScale = WorldScale(1, 1, 1);
	}
}

void WorldObject::InstantiateObject(WorldTransform worldPos)
{
	if (!ObjectInstantiated) {
		currentWorldTransform = worldPos;
	}
}

void WorldObject::DestroyObject()
{
}

void WorldObject::LoadMesh(TiraObjects objectTemplate)
{
	meshVertices = LoadMeshVerticesByTiraObjectTemplate(objectTemplate);
	//vertices layout
	vbLayout.Push<float>(3);
	//texture layout
	vbLayout.Push<float>(2);

	shaderSourcePath = (R"(C:\Projects\Software\Tira3D\Tira3D\resources\shaders\Basic.kliveshader)");
	textureFile = R"(C:\Projects\Software\Tira3D\Tira3D\resources\textures\TestTex3.jpg)";
}
