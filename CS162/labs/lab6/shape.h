#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>
#include <string>

using namespace std;

class Shape {
private:
	string name;
	string color;
public: 
	Shape(string, string);
	void setName(string);
	void setColor(string);
	string getName();
	string getColor();
	virtual float area() const = 0;
};

#endif
