#include <iostream>
#include <string>
#include "shape.h"
#include "rectangle.h"

using namespace std;

Rectangle::Rectangle(float width, float height) : Shape("rectangle","red") {
	this->width = width;
	this->height = height;
}

void Rectangle::setWidth(float width) {
	this->width = width;
}

void Rectangle::setHeight(float height) {
	this->height = height;
}

float Rectangle::getWidth() {
	return width;
}

float Rectangle::getHeight() {
	return height;
}

float Rectangle::area() const {
	float A = 0;
	A = width*height;
	return A;
}
