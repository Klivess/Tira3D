#include <iostream>
#include "Renderer/Tira3D.h";
using std::cout;
using std::endl;

int main() {

	try {
		Tira3D tira;
		//Create a window/viewport
		tira.InstantiateWindow(1280, 768, "Test!", NULL);





		tira.WaitUntilUserClosedWindow();
		cout << "Detected closed window. Closing..." << endl;
		return 0;
	}
	catch (std::exception error) {
		std::cout << error.what() << std::endl;
	}
}