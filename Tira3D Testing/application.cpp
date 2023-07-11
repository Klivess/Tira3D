#include <iostream>
#include "Renderer/Tira3D.h";
using namespace std;

int main() {

	try {
		Tira3D tira;
		//Initialise Tira3D
		if (!tira.Initialize()) {
			throw "it failed on the fucking INITALISE FUNCTION";
		}

		//Create a window/viewport
		tira.InstantiateWindow(1280, 768, "Test!", NULL);
		tira.CreateTriangle();

		cout << "rendering!" << endl;
		std::cin.get();

		return 0;
	}
	catch (std::exception error) {
		std::cout << error.what() << std::endl;
	}
}