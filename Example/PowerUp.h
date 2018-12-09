#pragma once
#include "Globals.h"

class PowerUp {

public:
	PowerUp(float x, float y, string name);
	~PowerUp();
	void toDisplayList(string name);
	GLuint getDisplayList();
	Vec2f getBoundingMin();
	Vec2f getBoundingMax();
	int getSecs();
	int setSecs();

private:
	float height = 5.0f;
	float width = 5.0f;
	vector<Vec2f> points;
	Vec2f boundingMinPoint;
	Vec2f boundingMaxPoint;
	GLuint display;
	string name;
	int seconds;
};