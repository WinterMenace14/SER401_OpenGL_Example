#pragma once
//#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <vector>
#include <GL/glut.h>
#include "ImathVec.h"

//define functions for finding the min and max of x and y positions
#define MIN2(a, b) (((a) < (b))?(a):(b))
#define MAX2(a, b) (((a) > (b))?(a):(b))

using namespace std;
using namespace Imath;

//typedef Vec3<float> Vec3f;
typedef Vec2<float> Vec2f;

//method to calculate the bounding box of the object
inline void calculateAABB(vector<Vec2f> &points, Vec2f &boundMin, Vec2f &boundMax) {

	vector<Vec2f> v = points;
	Vec2f boundingMinPoint = v[0];
	Vec2f boundingMaxPoint = v[0];

	//check to see if the vector is empty
	for (unsigned int i = 1; i < v.size(); i++) {
		boundingMinPoint.x = MIN2(boundingMinPoint.x, v[i].x);
		boundingMinPoint.y = MIN2(boundingMinPoint.y, v[i].y);
		boundingMaxPoint.x = MAX2(boundingMaxPoint.x, v[i].x);
		boundingMaxPoint.y = MAX2(boundingMaxPoint.y, v[i].y);
	}

	//set the new bounding points for the objects
	boundMin = boundingMinPoint;
	boundMax = boundingMaxPoint;
}
