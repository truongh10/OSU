#include <iostream>
#include <string>
#include "shape.h"
#include "circle.h"
#include <cmath>

using namespace std;

Circle::Circle(float radius) : Shape("Circle"," black") {
	this->radius = radius;
}

float Circle::getRadius() {
	return radius;
}

float Circle::area()const {
	float A = 0;
	A = pow(radius,2)*3.14;
	return A;
}
