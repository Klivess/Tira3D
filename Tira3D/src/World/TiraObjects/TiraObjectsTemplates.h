#pragma once
#include <vector>

enum TiraObjects {
	None,
	Cube
};

std::vector<float> LoadMeshVerticesByTiraObjectTemplate(TiraObjects object);
