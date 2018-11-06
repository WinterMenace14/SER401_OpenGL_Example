#pragma once

//include the header files of the game objects
#include "Ball.h"
#include "Keyboard.h"
#include <iostream>
#include "Player.h"

//define players movements
#define P1_UP	'w'
#define P1_DOWN	's'
#define	P2_UP	'i'
#define	P2_DOWN	'k'

//define the framerate of the game
#define FRAMERATE 60

class Pong {

//methods to render the game and the process along with framerate
public:
	//generic constructor & destructor
	Pong();
	~Pong();

	//handle the input and update of players and ball
	void init();
	void gameLoop();	//game loop
	void logic();		//read input and update objects
	void render();		//display objects to the screen
	Keyboard* getKeyboard();		//return the keyboard

//hold the objects of the game
private:
	Ball *ball;
	Player* p1;
	Player* p2;
	//Paddle *p1;
	//Paddle *p2;
	Keyboard *keyboard;

	//bool variables for running the game
	bool running = true;
};
