#ifndef DOG_H
#define DOG_H

#include "pet.h"

using namespace std;

class Dog : public Pet{
private:
	string breed;
public:
	Dog();
	void setBreed(string);
	string getBreed();
	string getLifespan();
};
#endif
