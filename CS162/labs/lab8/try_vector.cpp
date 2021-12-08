#include "./vector.hpp"
#include <vector>
#include <iostream>
#include <stdexcept>

using std::cout;
using std::endl;

int main() {

	vector<int> v; 		// Our vector class
	std::vector<int> stdv;	// Standard vector

	//Compare operation of out vector to std
	v.push_back(23);
	stdv.push_back(23);

	cout << "Our vector size: " << v.size() << endl;
	cout << "STL vector size: " << stdv.size() << endl;

	v.push_back(10);
	stdv.push_back(10);

	try {

		cout << v[1] << endl;
		cout << v[3] << endl;
	
		cout << v.at(3) << endl;
	}

	catch (std::exception& e) {
		cout << e.what() << endl;
	}

	cout << stdv.at(3) << endl;

	return 0;
}
