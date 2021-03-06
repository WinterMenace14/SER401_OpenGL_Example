/*
This is the main file to show a demonstration of OpenGL understanding. My Small application will demonstrate an understanding and show progress
of the understanding of the OpenGL API.

Author: Erik Isaacson
Date: 10/30/18

SER401
*/

//include OpenGL Lib
#include "Pong.h"

Pong pong;

//create callback functions
void idle() {
	pong.gameLoop();
}

void display() {
	pong.render();
}

void gameKeyboardDown(unsigned char key, int x, int y) {
	pong.getKeyboard()->readKeyboard(key, x, y, true);
}

void gameKeyboardUp(unsigned char key, int x, int y) {
	pong.getKeyboard()->readKeyboard(key, x, y, false);
}

// main
void main(int argc, char** argv) {
	glutInit(&argc, argv); // glut init
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1280, 720); // actual window size
	glutInitWindowPosition(0, 0); // window location
	glutCreateWindow("Pong Remake");
	pong.init();
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(gameKeyboardDown);
	glutKeyboardUpFunc(gameKeyboardUp);
	glutMainLoop(); //event loop
}