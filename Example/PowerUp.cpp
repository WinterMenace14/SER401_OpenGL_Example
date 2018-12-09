#include "PowerUp.h"

//constuctor for power up with specific name as identifier
PowerUp::PowerUp(float x, float y, string name) {

	this->name = name;

	//set passed in parameters to power up
	this->points.push_back(Vec2<GLfloat>(x, y));
	this->points.push_back(Vec2<GLfloat>(x, y - this->height));
	this->points.push_back(Vec2<GLfloat>(x + this->width, y - this->height));
	this->points.push_back(Vec2<GLfloat>(x + this->width, y));

	calculateAABB(this->points, this->boundingMinPoint, this->boundingMaxPoint);
	toDisplayList(this->name);
}

//destructor
PowerUp::~PowerUp() {
	//default destructor
}

//display method
void PowerUp::toDisplayList(string name) {
	float r = 0.0f, g = 0.0f, b = 0.0f;

	//iterate through the points and generate a display list
	this->display = glGenLists(1);
	glNewList(this->display, GL_COMPILE);

	//depending upon the string name switch the color of the powerup
	if (name == "BIG") {
		r = 0.0f, g = 0.0f, b = 1.0f;
	}

	//color of white for the paddle
	glColor3f(r, g, b);

	//begin the points for drawing
	glBegin(GL_QUADS);

	//iterate through all the points of the powerup
	for (unsigned int i = 0; i < this->points.size(); i++) {
		glVertex2f(this->points[i].x, this->points[i].y);
	}

	//end drawing and list
	glEnd();

	glEndList();
}

//return display list for powerup
GLuint PowerUp::getDisplayList() {
	return this->display;
}

//get bounding min
Vec2f PowerUp::getBoundingMin() {
	return this->boundingMinPoint;
}

//get bounding max
Vec2f PowerUp::getBoundingMax() {
	return this->boundingMaxPoint;
}

//get the seconds of life for the power up for the player
int PowerUp::getSecs() {
	return this->seconds;
}

//set the seconds for the life span
void PowerUp::setSecs(int lifeSpan) {
	this->seconds = lifeSpan;
}