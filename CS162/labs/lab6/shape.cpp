#include <iostream>
#include <string>
#include "shape.h"

using namespace std;

Shape::Shape(string name, string color) {
	this-> name  = name;
	this-> color = color;
}

void Shape::setName(string name) {
	this-> name = name;
}

void Shape::setColor(string color) {
	this-> color = color;
}	

string Shape::getName() {
	return name;
}

string Shape::getColor() {
	return color;
}

/*float Shape::area() const {
	return 0;
}*/






