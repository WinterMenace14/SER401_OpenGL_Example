#include "Ball.h"

Ball::Ball(float topLeftX, float topLeftY) {

	//set original position vector to passed in values
	this->origPos.x = topLeftX;
	this->origPos.y = topLeftY;

	//add initial values to points
	this->points.push_back(Vec2<GLfloat>(topLeftX, topLeftY));
	this->points.push_back(Vec2<GLfloat>(topLeftX, topLeftY - this->height));
	this->points.push_back(Vec2<GLfloat>(topLeftX + this->width, topLeftY - this->height));
	this->points.push_back(Vec2<GLfloat>(topLeftX + this->width, topLeftY));

	//create and set display list
	toDisplayList();

	//calculate bounding box
	calculateAABB(this->points, this->boundingMinPoint, this->boundingMaxPoint);

	//set speed of the ball
	setSpeed();

}

Ball::~Ball() {
	//generic destructor
}

//create display list
void Ball::toDisplayList() {

	//iterate through the points and generate a display list
	this->display = glGenLists(1);
	glNewList(this->display, GL_COMPILE);

	//color of white for the paddle
	glColor3f(1.0f, 1.0f, 1.0f);

	//begin the points for drawing
	glBegin(GL_QUADS);

	//iterate through all the points of the Paddle
	for (unsigned int i = 0; i < this->points.size(); i++) {
		glVertex2f(this->points[i].x, this->points[i].y);
	}

	//end drawing and list
	glEnd();

	glEndList();
}

//return the display list
GLuint Ball::getDisplayList() {
	return this->display;
}

//change the direction of the 
void Ball::changeDirection(Vec2f direction) {

	//update the speed vector of the ball
	this->speed.x = this->speed.x * direction.x;
	this->speed.y = this->speed.y * direction.y;
}

//up the speed of the ball
void Ball::upSpeed() {
	
	//check to see if the value is positive or negative to add .01 or -.01
	if (this->speed.x > 0) {
		this->speed.x += 0.1f;
	}
	else
		this->speed.x -= 0.1f;

	if (this->speed.y > 0) {
		this->speed.y += 0.1f;
	}
	else
		this->speed.y -= 0.1f;
}

bool Ball::collide(Paddle *p) {

	//create variables to hold the paddles bounding min and max vectors
	Vec2f paddleMin = p->getBoundMin();
	Vec2f paddleMax = p->getBoundMax();

	//set variables x and y to false
	int x = 0, y = 0;

	//begin to check the bounding areas of the ball with the paddles
	if ((this->boundingMinPoint.x >= paddleMin.x && this->boundingMinPoint.x <= paddleMax.x)
		|| (this->boundingMaxPoint.x >= paddleMin.x && this->boundingMaxPoint.x <= paddleMax.x)
		|| (paddleMin.x >= this->boundingMinPoint.x && paddleMin.x <= this->boundingMinPoint.x)
		|| (paddleMax.x >= this->boundingMinPoint.x && paddleMax.x <= this->boundingMaxPoint.x))
		x = 1;

	if ((this->boundingMinPoint.y >= paddleMin.y && this->boundingMinPoint.y <= paddleMax.y)
		|| (this->boundingMaxPoint.y >= paddleMin.y && this->boundingMaxPoint.y <= paddleMax.y)
		|| (paddleMin.y >= this->boundingMinPoint.y && paddleMin.y <= this->boundingMinPoint.y)
		|| (paddleMax.y >= this->boundingMinPoint.y && paddleMax.y <= this->boundingMaxPoint.y))
		y = 1;

	if (x == 1 && y == 1)
		return true;
	else
		return false;
}

//check to see if the ball hits the bounds of the window
bool Ball::collideWithBounds() {

	//check if the ball hits the top of the window
	if (this->points[0].y >= 100.0f || this->points[0].y <= -90.0f) {
		return true;
	}
	else
		return false;
}

//update the position of the ball
void Ball::updatePos() {
	
	//update the position of the ball
	for (unsigned int i = 0; i < this->points.size(); i++) {
		this->points[i].x += this->speed.x;
		this->points[i].y += this->speed.y;
	}

	//calculate new bounding box
	calculateAABB(this->points, this->boundingMinPoint, this->boundingMaxPoint);

	//delete the old display list
	glDeleteLists(this->display, 1);
	this->toDisplayList();

}

//get the farthest and shortest x values
float Ball::getMinX() {
	return this->boundingMinPoint.x;
}

float Ball::getMaxX() {
	return this->boundingMaxPoint.x;
}

//reset the ball to it's original position
void Ball::resetBall() {

	this->points[0] = (Vec2<GLfloat>)this->origPos;
	this->points[1] = (Vec2<GLfloat>(this->origPos.x, this->origPos.y - this->height));
	this->points[2] = (Vec2<GLfloat>(this->origPos.x + this->width, this->origPos.y - this->height));
	this->points[3] = (Vec2<GLfloat>(this->origPos.x + this->width, this->origPos.y));

	//calculate new bounding box
	calculateAABB(this->points, this->boundingMinPoint, this->boundingMaxPoint);

	//delete the old display list
	glDeleteLists(this->display, 1);
	this->toDisplayList();
	
}

//set the speed of the ball
void Ball::setSpeed() {

	//set the speed vector of the ball
	srand(time(NULL));
	int x = (rand() % 4);
	switch (x) {

	case 0:
		this->speed.x = -0.5f;
		this->speed.y = 0.5f;
		break;

	case 1:
		this->speed.x = -0.5f;
		this->speed.y = -0.5f;
		break;

	case 2:
		this->speed.x = 0.5f;
		this->speed.y = -0.5f;
		break;

	case 3:
		this->speed.x = 0.5f;
		this->speed.y = 0.5f;
		break;
	}
}