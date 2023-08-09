#include "Tira3D.h"
#include "Tira3DRendering.h"
Tira3D::Tira3D()
{
	tiraInput = TiraInput();
}
Tira3D::~Tira3D()
{
}
//Instantiate a window
//OpenGL is a 'state machine' type library which only runs on one thread, so this code will open up a new thread for OpenGL draw calls.
void Tira3D::InstantiateWindow(int width, int height, const char* title, GLFWmonitor* monitor) {
	renderThreadClass.WindowClosed = &UserClosedWindow;
	// Create a thread
	renderThread = std::thread(&Tira3DRendering::CreateRender, &renderThreadClass, width, height, title, monitor);
	//wait for window to instantiate
	while (renderThreadClass.WindowInstantiated == false) {}
	WindowIsCreated = true;
	//renderThread = std::thread(renderThreadClass.CreateRender(), width, height, title, monitor);
	//AttachProcessToRenderThread(funcPointer, 50);
}

void Tira3D::WaitUntilUserClosedWindow() {
	while (UserClosedWindow == false) {}
	renderThread.join();
	return;
}

TiraInput& Tira3D::Inputs()
{
	return tiraInput;
}

Camera& Tira3D::CreateCamera(WorldPosition position, WorldRotation rotation, float sensitivity, float FOV)
{
	AttachedCamera = new Camera(position, rotation, FOV, &(renderThreadClass.WindowWidth), &(renderThreadClass.WindowHeight), sensitivity);
	if (WindowIsCreated) {
		renderThreadClass.currentCamera = AttachedCamera;
	}
	return *AttachedCamera;
}