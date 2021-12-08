#include "dog.h"
#include "pet.h"

using namespace std;

Dog::Dog() {
	breed = "";
}

void Dog::setBreed(string breed){
	this->breed = breed;
}

string Dog::getBreed() {
	return breed;
}

string Dog::getLifespan() {
	if (weight > 100) 
		return "Approximately 7 years";
	else return "Approximately 13 years";
}
