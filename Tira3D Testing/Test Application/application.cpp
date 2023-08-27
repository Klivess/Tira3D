#include <iostream>
#include "Renderer/Tira3D.h"
#include <stdlib.h>
#include <chrono>

using std::cout;
using std::endl;

Tira3D tira;
void SetupTiraInputs() {
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
	tira.Inputs().RecordInput(TiraKey::TIRA_KEY_LEFT_CONTROL, [&]() {
		tira.AttachedCamera->m_Movement.MoveDown();
		});

	//Changing speed
	tira.Inputs().RecordInput(TiraKey::TIRA_KEY_SCROLL_UP, [&]() {
		tira.AttachedCamera->m_Movement.SetMovementSpeed(tira.AttachedCamera->m_Movement.GetMovementSpeed() * 1.1);
		});
	tira.Inputs().RecordInput(TiraKey::TIRA_KEY_SCROLL_DOWN, [&]() {
		tira.AttachedCamera->m_Movement.SetMovementSpeed(tira.AttachedCamera->m_Movement.GetMovementSpeed() / 1.1);
		});

	//Checking position in world
	tira.Inputs().RecordInput(TiraKey::TIRA_KEY_1, [&]() {
		cout << ("I am at x:" + std::to_string(tira.AttachedCamera->transform.worldPosition.x)
			+ " y: " + std::to_string(tira.AttachedCamera->transform.worldPosition.y)
			+ " z: " + std::to_string(tira.AttachedCamera->transform.worldPosition.z)) << endl;;
		}, TIRA_PRESS);
}

void main() {

	try {
		//Create a window/viewport
		tira.InstantiateWindow(1280, 768, "Test!", NULL);

		//Create our camera that we possess
		tira.CreateCamera(WorldPosition(0, 0, 3), WorldRotation(0, 0, 0));

		//Set void colour to red
		tira.Designer().SetVoidColour(200, 0, 0, 0.5);

		//Setup our inputs (Tira3D Testing function only)
		SetupTiraInputs();

		//Create our cube
		auto& obj = tira.Designer().CreateNewWorldObject("MyCube");
		obj.SetWorldPosition(WorldPosition(0, 0, 0));
		obj.LoadMesh(TiraObjects::Cube);
		obj.LoadTexture(R"(C:\Projects\Software\Tira3D\Tira3D Testing\Assets\Textures\onepiecesucks.jpg)");
		obj.SetColour(ObjectColour(0, 0, 255, 1));


		//Animate our cube to oscillate vertically
		float x = 0;
		while (true)
		{
			x += 0.1;
			using namespace std::this_thread;     // sleep_for, sleep_until
			using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
			using std::chrono::system_clock;

			float height = cos(x) * 0.05;
			cout << height << endl;
			obj.SetWorldPosition(obj.currentWorldTransform.worldPosition.MoveUp(height));
			sleep_for(10ms);
		}


		tira.WaitUntilUserClosedWindow();
		delete& tira;
	}
	catch (std::exception error) {
		std::cout << error.what() << std::endl;
	}
}