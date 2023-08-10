#include <iostream>
#include "Renderer/Tira3D.h"
#include <stdlib.h>
using std::cout;
using std::endl;


void zaza() {

}

void main() {

	try {
		Tira3D tira;
		//Create a window/viewport
		tira.InstantiateWindow(1280, 768, "Test!", NULL);

		tira.CreateCamera(WorldPosition(0, 0, 3), WorldRotation(0, 0, 0));

		for (int i = 0; i < 1000; i++)
		{
			auto& obj = tira.Designer().CreateNewWorldObject("MyCube");
			obj.SetWorldPosition(WorldPosition(rand() % 100, rand() % 100, rand() % 100));
			obj.LoadMesh(TiraObjects::Cube);
		}

		//Moving around
		tira.Inputs().RecordInput(TiraKey::TIRA_KEY_W, [&]() {
			tira.AttachedCamera->m_Movement.MoveForward();
			});
		tira.Inputs().RecordInput(TiraKey::TIRA_KEY_S, [&]() {
			tira.AttachedCamera->m_Movement.MoveBack();
			});
		tira.Inputs().RecordInput(TiraKey::TIRA_KEY_A, [&]() {
			tira.AttachedCamera->m_Movement.MoveLeft();
			});
		tira.Inputs().RecordInput(TiraKey::TIRA_KEY_D, [&]() {
			tira.AttachedCamera->m_Movement.MoveRight();
			});
		tira.Inputs().RecordInput(TiraKey::TIRA_KEY_SPACE, [&]() {
			tira.AttachedCamera->m_Movement.MoveUp();
			});
		tira.Inputs().RecordInput(TiraKey::TIRA_KEY_C, [&]() {
			tira.AttachedCamera->m_Movement.MoveDown();
			});

		tira.WaitUntilUserClosedWindow();
		delete& tira;
	}
	catch (std::exception error) {
		std::cout << error.what() << std::endl;
	}
}