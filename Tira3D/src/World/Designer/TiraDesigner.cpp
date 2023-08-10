#include "TiraDesigner.h"

WorldObject& TiraDesigner::CreateNewWorldObject(std::string name)
{
	WorldObject& obj = renderParent->CreateNewWorldObject(name);
	return obj;
}
