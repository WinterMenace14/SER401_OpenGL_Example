/*
This is the main file to show a demonstration of OpenGL understanding. My Small application will demonstrate an understanding and show progress
of the understanding of the OpenGL API.

Author: Erik Isaacson
Date: 10/30/18

SER401
*/

//include OpenGL Lib
#include "Paddle.h"
#include "Ball.h"

//set global objects
Paddle *p1;
Paddle *p2;
Ball *ball;

void myInit() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0); // color maroon
	glMatrixMode(GL_PROJECTION); // projection
	glLoadIdentity();
	gluOrtho2D(-100.0, 100.0, -100.0, 100.0); // units inside

	//create Paddle object
	p1 = new Paddle(-75.0f, 85.0f);
	p2 = new Paddle(70.0f, 85.0f);
	ball = new Ball(-2.5f, 2.5f);
}

//create keyboard callback function
void myKeyboard(unsigned char key, int x, int y) {

	//pass key value to update position method and redisplay the Paddle
	if (key == 'w' || key == 's') {

		//check movement based on key
		if (key == 'w') {
			p1->updatePos(3.0f);
		}
		else {
			p1->updatePos(-3.0f);
		}
	}

	else if (key == 'i' || key == 'k') {

		if (key == 'i') {
			p2->updatePos(3.0f);
		}
		else {
			p2->updatePos(-3.0f);
		}
	}
	glutPostRedisplay();

}

/**
 *  myDisplay
 */
void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT); // clear the window

	//check to see if the ball is in bounds between -110 and 110
	//if so, reset the ball otherwise, play game as normal
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

		glCallList(ball->getDisplayList());
		glCallList(p1->getDisplayList());
		glCallList(p2->getDisplayList());
		//practice Paddle placement inital top left coordinates x:-70 y:85

		glutSwapBuffers(); //forces commands to execute
	}
}

// main
void main(int argc, char** argv) {
	glutInit(&argc, argv); // glut init
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1280, 720); // actual window size
	glutInitWindowPosition(0, 0); // window location
	glutCreateWindow("Pong Remake");
	myInit();
	glutDisplayFunc(myDisplay);
	glutIdleFunc(myDisplay);
	glutKeyboardFunc(myKeyboard);
	glutMainLoop(); //event loop
}