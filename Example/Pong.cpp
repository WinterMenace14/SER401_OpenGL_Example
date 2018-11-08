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
	this->p1 = new Player(-75.0f, 85.0f);
	this->p2 = new Player(70.0f, 85.0f);
	this->keyboard = new Keyboard();
}

void Pong::render() {
	//clear the screen
	glClear(GL_COLOR_BUFFER_BIT); // clear the window

	//display scoreboard
	scoreBoard();

	//display each of the objects
	glCallList(this->ball->getDisplayList());
	glCallList(this->p1->getPaddle()->getDisplayList());
	glCallList(this->p2->getPaddle()->getDisplayList());

	glutSwapBuffers();
}

//method to display the score of both players
void Pong::scoreBoard() {

	//variable to store scores
	string score;

	//render the scores of the players to the screen
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(-90.0f, 70.0f);
	score = to_string(this->p1->getScore());
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)score[0]);
	glScalef(2.0f, 2.0f, 1.0f);
	glPopMatrix();

	//player 2 score
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(85.0f, 70.0f);
	score = to_string(this->p2->getScore());
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)score[0]);
	glScalef(2.0f, 2.0f, 1.0f);
	glPopMatrix();
}

//handle the logic of the game
void Pong::logic() {

	//read in input
	if (this->keyboard->getKeys()[P1_UP]) {
		this->p1->getPaddle()->updatePos(3.0f);
	}

	if (this->keyboard->getKeys()[P1_DOWN]) {
		this->p1->getPaddle()->updatePos(-3.0f);
	}

	if (this->keyboard->getKeys()[P2_UP]) {
		this->p2->getPaddle()->updatePos(3.0f);
	}

	if (this->keyboard->getKeys()[P2_DOWN]) {
		this->p2->getPaddle()->updatePos(-3.0f);
	}

	//get the logic of the ball
	if (ball->getMinX() <= -110.0f || ball->getMaxX() >= 110.0f) {

		//check which side of the screen the ball left
		if (ball->getMinX() <= -110.0f) {
			//award player to a point
			p2->addToScore();
		}

		if (ball->getMaxX() >= 110.0f) {
			p1->addToScore();
		}

		ball->resetBall();
		ball->setSpeed();
	}

	else {
		//check the bounds of the window if the ball
		if (ball->collideWithBounds()) {
			ball->changeDirection(Vec2<float>(1.0f, -1.0f));
		}

		//check if the ball collides with player 1
		if (ball->collide(p1->getPaddle()) && ball->getMinX() > p1->getPaddle()->getBoundMin().x) {
			p1->getPaddle()->setLastHit(true);
			p2->getPaddle()->setLastHit(false);
			ball->changeDirection(Vec2<float>(-1.0f, 1.0f));
			ball->upSpeed();
		}

		//check if the ball collides with player 2
		if (ball->collide(p2->getPaddle()) && ball->getMaxX() < p2->getPaddle()->getBoundMax().x) {
			p2->getPaddle()->setLastHit(true);
			p1->getPaddle()->setLastHit(false);
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

	//check to see if one of the players reach 7
	if (this->p1->getScore() == 7 || this->p2->getScore() == 7) {

		//reset player scores to 0
		this->p1->resetScore();
		this->p2->resetScore();
	}
}