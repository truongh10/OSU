#include "pet.h"

using namespace std;

Pet::Pet() {
	name = "";
	weight = 0;
}

void Pet::setName(string name) {
	this->name = name;
}

void Pet::setWeight(int weight) {
	this->weight = weight;
}

string Pet::getName() {
	return name;
}

int Pet::getWeight() {
	return weight;
}

string Pet::getLifespan() {
	return "unknown lifespan";
}
