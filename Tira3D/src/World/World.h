#pragma once

class WorldPosition {
public:
	WorldPosition CreateWorldPosition(float x, float y, float z);
	float x;
	float y;
	float z;
};

class WorldScale {
public:
	WorldScale CreateWorldScale(float x, float y, float z) {
		this->x=x;
		this->y=y;
		this->z=z;
	}
	float x = 1;
	float y = 1;
	float z = 1;
};

class WorldTransform {
public:
	WorldTransform CreateTransform(WorldPosition position, WorldScale scale) {
		this->position.x = position.x;
		this->scale.x = scale.x;
	}
	WorldPosition position;
	WorldScale scale;
};

class World
{
};

