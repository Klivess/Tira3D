#include <iostream>
#include "src/Renderer/Tira3D.h"

int main() {
	Tira3D::Initialize();
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	auto window = Tira3D::InstantiateWindow(1280, 768, "Test!", monitor);
	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return 0;
}