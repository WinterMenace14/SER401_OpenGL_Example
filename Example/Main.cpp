/*
This is the main file to show a demonstration of OpenGL understanding. My Small application will demonstrate an understanding and show progress
of the understanding of the OpenGL API.

Author: Erik Isaacson
Date: 10/30/18

SER401
*/

//include OpenGL Lib
#include "Paddle.h"

//set global objects
Paddle *p1;
Paddle *p2;

void myInit() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0); // color maroon
	glMatrixMode(GL_PROJECTION); // projection
	glLoadIdentity();
	gluOrtho2D(-100.0, 100.0, -100.0, 100.0); // units inside

	//create Paddle object
	p1 = new Paddle(-75.0f, 85.0f);
	p2 = new Paddle(70.0f, 85.0f);
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

	glCallList(p1->getDisplayList());
	glCallList(p2->getDisplayList());
	//practice Paddle placement inital top left coordinates x:-70 y:85

	glutSwapBuffers(); //forces commands to execute
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
	glutKeyboardFunc(myKeyboard);
	glutMainLoop(); //event loop
}