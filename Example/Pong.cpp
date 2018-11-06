#include "Pong.h"

Pong::Pong() {
	//generic constructor
}

Pong::~Pong() {
	//generic destructor
}

//init function
void Pong::init() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0); // color maroon
	glMatrixMode(GL_PROJECTION); // projection
	glLoadIdentity();
	gluOrtho2D(-100.0, 100.0, -100.0, 100.0); // units inside

	this->ball = new Ball(-2.5f, 2.5f);
	this->p1 = new Paddle(-75.0f, 85.0f);
	this->p2 = new Paddle(70.0f, 85.0f);
	this->keyboard = new Keyboard();
}

void Pong::render() {
	//clear the screen
	glClear(GL_COLOR_BUFFER_BIT); // clear the window

	//display each of the objects
	glCallList(this->ball->getDisplayList());
	glCallList(this->p1->getDisplayList());
	glCallList(this->p2->getDisplayList());

	glutSwapBuffers();
}

//handle the logic of the game
void Pong::logic() {

	//read in input
	if (this->keyboard->getKeys()[P1_UP]) {
		this->p1->updatePos(3.0f);
	}

	if (this->keyboard->getKeys()[P1_DOWN]) {
		this->p1->updatePos(-3.0f);
	}

	if (this->keyboard->getKeys()[P2_UP]) {
		this->p2->updatePos(3.0f);
	}

	if (this->keyboard->getKeys()[P2_DOWN]) {
		this->p2->updatePos(-3.0f);
	}

	//get the logic of the ball
	if (ball->getMinX() <= -110.0f || ball->getMaxX() >= 110.0f) {
		ball->resetBall();
		ball->setSpeed();
	}

	else {
		//check the bounds of the window if the ball
		if (ball->collideWithBounds()) {
			ball->changeDirection(Vec2<float>(1.0f, -1.0f));
		}

		//check if the ball collides with player 1
		if (ball->collide(p1) && ball->getMinX() > p1->getBoundMin().x) {
			ball->changeDirection(Vec2<float>(-1.0f, 1.0f));
			ball->upSpeed();
		}

		//check if the ball collides with player 2
		if (ball->collide(p2) && ball->getMaxX() < p2->getBoundMax().x) {
			ball->changeDirection(Vec2<float>(-1.0f, 1.0f));
			ball->upSpeed();
		}

		//update the position of the ball
		ball->updatePos();
	}
}

//return the keyboard
Keyboard* Pong::getKeyboard() {
	return this->keyboard;
}

//game loop function
void Pong::gameLoop() {

	//create variables for getting time difference
	//and setting frame rate
	int t1, t2;

	t1 = glutGet(GLUT_ELAPSED_TIME);

	//check to see if the game is still running
	if (running) {

		//update logic
		logic();

		//render the updated positions of the ball and paddles
		render();
	}

	do {
		t2 = glutGet(GLUT_ELAPSED_TIME);
	} while (t2 - t1 < 1000 / FRAMERATE);
}