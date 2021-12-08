#ifndef PET_H
#define PET_H
#include <iostream>
#include <string> 

using namespace std;

class Pet {
protected:
	string name;
	int weight;
public:
	Pet();
	// mutators
	void setName(string);
	void setWeight(int);
	// accessors
	string getName();
	int getWeight();
	virtual string getLifespan();
};

#endif












