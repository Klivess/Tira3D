#pragma once
class ObjectColour {
public:
	ObjectColour() {
		r = 255;
		g = 255;
		b = 255;
		a = 255;
	}
	ObjectColour(float red, float green, float blue, float alpha) {
		r = red;
		g = green;
		b = blue;
		a = alpha;
	}
	float r;
	float g;
	float b;
	float a;
};

class ObjectAttributes
{
};

