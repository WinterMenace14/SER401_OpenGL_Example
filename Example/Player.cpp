#include "Player.h"

//constructor
Player::Player(float x, float y) {

	//set score to 0 and create paddle
	this->paddle = new Paddle(x, y);
	this->score = 0;
}

//generic destructor
Player::~Player() {
	//do things
}

//get the current score of the player
unsigned int Player::getScore() {
	return this->score;
}

//up the players score
void Player::addToScore() {
	this->score += 1;
}

//get the paddle of the player
Paddle* Player::getPaddle() {
	return this->paddle;
}

//set player score to 0
void Player::resetScore() {
	this->score = 0;
}

//return the player has a powerup
bool Player::hasPowerUp() {
	return this->hasPowerUp;
}

//set that the player has a powerup
void Player::setPowerUp() {
	if (this->hasPowerUp()) {
		this->powerUp = false;
	}

	else {
		this->powerUp = true;
	}
}