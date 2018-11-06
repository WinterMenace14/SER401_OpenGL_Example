#pragma once
#include "Paddle.h"

class Player {

public:
	Player(float x, float y);
	~Player();
	void addToScore();
	unsigned int getScore();
	Paddle* getPaddle();
	void resetScore();

private:
	Paddle* paddle;
	unsigned int score;
};