#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <iostream>
#include <string>

using namespace std;

class Rectangle : public Shape {
private:
	float width;
	float height;
public:
	Rectangle(float, float);
	void setWidth(float width);
	void setHeight(float height);
	float getWidth();
	float getHeight();
	float area() const override;
};

#endif
