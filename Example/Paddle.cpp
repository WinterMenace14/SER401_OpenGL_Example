#include "Paddle.h"

//constructor
Paddle::Paddle(float topLeftX, float topLeftY) {

	//add inital values to points
	this->points.push_back(Vec2<GLfloat>(topLeftX, topLeftY));
	this->points.push_back(Vec2<GLfloat>(topLeftX, topLeftY - this->height));
	this->points.push_back(Vec2<GLfloat>(topLeftX + this->width, topLeftY - this->height));
	this->points.push_back(Vec2<GLfloat>(topLeftX + this->width, topLeftY));

	//create and set display list
	toDisplayList();
	calculateAABB(this->points, this->boundingMinPoint, this->boundingMaxPoint);
}

//destructor
Paddle::~Paddle() {
	//generic destroyer
}

void Paddle::toDisplayList() {

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

GLuint Paddle::getDisplayList() {
	return this->display;
}

//update the position of the paddle
void Paddle::updatePos(float value) {

	//based on value being positive or negative, travel up or down
	if (value > 0.0f) {

		//check first point height
		if (this->points[0].y >= 85.0f) {
			
			//return out of the function, nothing to be done
			return;
			//set all points to be as they were
			/*for (unsigned int i = 0; i < this->points.size(); i++) {
				this->points[i].y = this->points[i].y; //don't do anything
			}*/
		}
		else {

			//iterate through all points and update positon of Paddle
			for (unsigned int i = 0; i < this->points.size(); i++) {
				this->points[i].y += 3.0f;
			}
		}		
	}

	else if (value < 0.0f) {

		//check 2nd point height
		if (this->points[1].y <= -85.0f) {

			//return out of the function
			return;
		}
		else {

			//iterate through all points and update positon of Paddle
			for (unsigned int i = 0; i < this->points.size(); i++) {
				this->points[i].y -= 3.0f;
			}
		}
	}

	//calculate the new bounding box
	calculateAABB(this->points, this->boundingMinPoint, this->boundingMaxPoint);

	//after updating points delete the original display list and create new one
	glDeleteLists(this->display, 1);
	this->toDisplayList();
}

//return bounding min point
Vec2f Paddle::getBoundMin() {
	return this->boundingMinPoint;
}

//return bounding max point
Vec2f Paddle::getBoundMax() {
	return this->boundingMaxPoint;
}