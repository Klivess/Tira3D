#pragma once
#include "../../WorldObjects/WorldObject.h"
#include "../../Renderer/Tira3DRendering.h"

class TiraDesigner
{
public:
	Tira3DRendering* renderParent = nullptr;

	WorldObject& CreateNewWorldObject(std::string name);

private:

};

