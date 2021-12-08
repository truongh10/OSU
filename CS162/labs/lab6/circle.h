#ifndef CIRCLE_H
#define CIRCLE_H

#include <iostream>
#include <string>
#include "shape.h"

using namespace std;

class Circle : public Shape {
private:
	float radius;
public:
	Circle(float);
	void setRadius(float);
	float getRadius();
	virtual float area()const;
};
#endif
