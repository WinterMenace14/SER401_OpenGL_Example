#pragma once
#include "Globals.h"

//create a class for the paddle of the pong game
class Paddle {

public:
	Paddle(float topLeftX, float topLeftY);
	~Paddle();
	void toDisplayList();
	GLuint getDisplayList();
	void updatePos(float value);
	Vec2f getBoundMin();
	Vec2f getBoundMax();

private:
	float width = 5.0f;
	float height = 35.0f;
	vector<Vec2f> points;
	Vec2f boundingMinPoint;
	Vec2f boundingMaxPoint;
	GLuint display;
};
