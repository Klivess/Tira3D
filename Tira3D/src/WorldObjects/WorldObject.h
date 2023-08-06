#include "../Renderer/Tira3DRendering.h"
#include <iostream>
#include "../World/World.h"
#pragma once

enum TiraObjects {
	None,
	Cube
};

class WorldObject
{
public:
	WorldTransform currentWorldTransform;

	WorldObject(Tira3DRendering* client) {
		this->RenderClient = client;
	}
	std::vector<int> positions;
	Tira3DRendering* RenderClient = nullptr;

	void InstantiateObject(WorldPosition worldPos);
	void InstantiateObject(WorldTransform worldPos);
};
