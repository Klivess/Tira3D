#include <iostream>
#include "Renderer/Tira3D.h"
using std::cout;
using std::endl;

void main() {

	try {
		Tira3D tira;
		//Create a window/viewport
		tira.InstantiateWindow(1280, 768, "Test!", NULL);
		tira.WaitUntilUserClosedWindow();
	}
	catch (std::exception error) {
		std::cout << error.what() << std::endl;
	}
}