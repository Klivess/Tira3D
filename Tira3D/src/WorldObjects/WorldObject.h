#include "../Renderer/Tira3D.h"
#include <iostream>
#include "../World/World.h"

#pragma once
class WorldObject
{
public:
	WorldObject(Tira3DRendering* client) {
		this->RenderClient = client;
	}
	vector<int> positions;
	Tira3DRendering* RenderClient = nullptr;

	void InstantiateObject(WorldPosition worldPos);
	void InstantiateObject(WorldTransform worldPos);
};

