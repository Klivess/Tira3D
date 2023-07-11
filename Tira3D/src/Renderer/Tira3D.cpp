#include "Tira3D.h"
//Initialise Tira3D (GLFW) 
bool Tira3D::Initialize() {
	bool result = renderThreadClass.InitialiseRender();
	return result;
}

//Instantiate a window
//OpenGL is a 'state machine' type library which only runs on one thread, so this code will open up a new thread for OpenGL draw calls.
void Tira3D::InstantiateWindow(int width, int height, const char* title, GLFWmonitor* monitor) {
	// Create a thread
	renderThreadClass = Tira3DRenderThread{};
	renderThread = std::thread(&Tira3DRenderThread::CreateRender, &renderThreadClass, width, height, title, monitor);
	
	while(renderThreadClass.WindowInstantiated==false){}

	//renderThread = std::thread(renderThreadClass.CreateRender(), width, height, title, monitor);
	//AttachProcessToRenderThread(funcPointer, 50);
}

void Tira3D::CreateTriangle() {
	renderThreadClass.DrawTriangle();
}