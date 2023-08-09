#include <iostream>
#include "Renderer/Tira3D.h"
using std::cout;
using std::endl;


void zaza() {

}

void main() {

	try {
		Tira3D tira;
		//Create a window/viewport
		tira.InstantiateWindow(1280, 768, "Test!", NULL);

		tira.CreateCamera(WorldPosition(0, 0, -3), WorldRotation(0, 0, 0));


		//tira.Inputs().RecordInput(TiraKey::TIRA_KEY_W, tira.AttachedCamera.m_Movement.MoveForward));

		tira.WaitUntilUserClosedWindow();
		delete& tira;
	}
	catch (std::exception error) {
		std::cout << error.what() << std::endl;
	}
}