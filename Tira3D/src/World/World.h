#pragma once

class WorldPosition {
public:
	WorldPosition() {
		x = 0;
		y = 0;
		z = 0;
	}
	WorldPosition(float X, float Y, float Z) :
		x(X), y(Y), z(Z) {}
	float x;
	float y;
	float z;

	void MoveRight(float amount) {
		x + amount;
	}
	void MoveForward(float amount) {
		z + amount;
	}

};

class WorldRotation {
public:
	WorldRotation() {
		x = 0;
		y = 0;
		z = 0;
	}
	WorldRotation(float X, float Y, float Z) :
		x(X), y(Y), z(Z) {}
	float x;
	float y;
	float z;
};

class WorldScale {
public:
	WorldScale() {
		x = 0;
		y = 0;
		z = 0;
	}
	WorldScale(float X, float Y, float Z) :
		x(X), y(Y), z(Z) {}
	float x;
	float y;
	float z;
};

class WorldTransform {
public:
	WorldTransform() {
		worldPosition = WorldPosition(0, 0, 0);
		worldScale = WorldScale(1, 1, 1);

	}
	WorldTransform(WorldPosition position, WorldRotation Rotation, WorldScale scale) :
		worldPosition(position), worldScale(scale), worldRotation(Rotation) {}
	WorldPosition worldPosition;
	WorldRotation worldRotation;
	WorldScale worldScale;
};

class World
{
};

