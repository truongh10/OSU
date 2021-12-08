#include <iostream>
#include <string>
#include "shape.h"
#include "rectangle.h"
#include "circle.h"
#include "square.h"

using namespace std;


bool operator <(const Shape &s1, const Shape &s2) {
	if (s1.area() < s2.area())
		return true;
	else 
		return false;
}
	
bool operator >(const Shape &s1, const Shape &s2) {
	if (s1.area() > s2.area())
		return true;
	else
		return false;
}

void print_shape_info (Shape &s) {
	cout << "Shape: " << s.getName() << endl;
	cout << "Color: " << s.getColor() << endl;
	cout << "Area: " << s.area() << endl;
}


int main() {
/*	Shape a("triangle","blue");
	cout << "shape: " << a.getName() << endl;
	cout << "Color: " << a.getColor() << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
*/
	Rectangle r(10.0,5.0);
	cout << "Shape: " << r.getName() << endl;
	cout << "Color: " << r.getColor() << endl;
	cout << "Area: " << r.area() << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	
	Circle c(10);
	cout << "Shape: " << c.getName() << endl;
	cout << "Color: " << c.getColor() << endl;
	cout << "Area: " << c.area() << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	
	Square s;
	cout << "Shape: " << s.getName() << endl;
	cout << "Color: " << s.getColor() << endl;
	cout << "Area: " << s.area() << endl;


	cout << "=====================================" << endl;
	print_shape_info(r);
	cout << "=====================================" << endl;
	print_shape_info(c);
	cout << "=====================================" << endl;
	print_shape_info(s);







	return 0;
}
