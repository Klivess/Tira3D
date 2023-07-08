#include "pch.h";
#include <iostream>
#include "Renderer/Tira3D.h";


int main() {
	Tira3D tira;
	//Initialise Tira3D
	tira.Initialize();

	//Create a window/viewport
	tira.InstantiateWindow(1280, 768, "Test!", NULL);
	return 0;
}