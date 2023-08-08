#include <iostream>
#include "Renderer/Tira3D.h"
using std::cout;
using std::endl;

void main() {

	try {
		Tira3D tira;
		//Create a window/viewport
		tira.InstantiateWindow(1280, 768, "Test!", NULL);

		tira.CreateCamera(WorldPosition(0, 0, -3), WorldRotation(0, 0, 0));
		tira.AttachedCamera->SetMovementKeys(TiraKey::TIRA_KEY_W,
			TiraKey::TIRA_KEY_S,
			TiraKey::TIRA_KEY_D,
			TiraKey::TIRA_KEY_A,
			TiraKey::TIRA_KEY_SPACE,
			TiraKey::TIRA_KEY_C);

		tira.WaitUntilUserClosedWindow();
	}
	catch (std::exception error) {
		std::cout << error.what() << std::endl;
	}
}