#include "Tira3D.h"
//Instantiate a window
//OpenGL is a 'state machine' type library which only runs on one thread, so this code will open up a new thread for OpenGL draw calls.
void Tira3D::InstantiateWindow(int width, int height, const char* title, GLFWmonitor* monitor) {
	renderThreadClass.WindowClosed = &UserClosedWindow;
	// Create a thread
	renderThread = std::thread(&Tira3DRendering::CreateRender, &renderThreadClass, width, height, title, monitor);
	//wait for window to instantiate
	while (renderThreadClass.WindowInstantiated == false) {}
	//renderThread = std::thread(renderThreadClass.CreateRender(), width, height, title, monitor);
	//AttachProcessToRenderThread(funcPointer, 50);
}

void Tira3D::WaitUntilUserClosedWindow() {
	while (UserClosedWindow == false) {}
	renderThread.join();
	return;
}

WorldObject Tira3D::CreateWorldObject(TiraObjects object, WorldPosition position, WorldScale scale)
{
	WorldObject worldObj(&renderThreadClass);
	worldObj.currentWorldTransform.position = position;
	worldObj.currentWorldTransform.scale = scale;
	return worldObj;
}
