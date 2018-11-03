#pragma once
#include "Globals.h"
#include "Paddle.h"

//Ball class
class Ball {

public:
	Ball(float topLeftX, float topLeftY);
	~Ball();
	void toDisplayList();
	GLuint getDisplayList();
	void updatePos();
	bool collide(Paddle *p);
	void changeDirection(Vec2f direction);
	void upSpeed();
	bool collideWithBounds();
	float getMinX();
	float getMaxX();
	void resetBall();
	void setSpeed();

private:
	Vec2f origPos;
	float width = 5.0f;
	float height = 10.0f;
	Vec2f speed;
	vector<Vec2f> points;
	Vec2f boundingMinPoint;
	Vec2f boundingMaxPoint;
	GLuint display;
};