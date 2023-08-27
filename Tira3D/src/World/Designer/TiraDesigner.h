#pragma once
#include "../../WorldObjects/WorldObject.h"
#include "../../Renderer/Tira3DRendering.h"

class TiraDesigner
{
public:
	Tira3DRendering* renderParent = nullptr;

	WorldObject& CreateNewWorldObject(std::string name);
	void SetVoidColour(float r, float g, float b, float a = 1) {
		renderParent->VoidColour.r = r;
		renderParent->VoidColour.g = g;
		renderParent->VoidColour.b = b;
		renderParent->VoidColour.a = a;
	}
private:

};

