#include <iostream>
#include <string>
#include "pet.h"
#include "dog.h"

using namespace std;

int main() {
	Pet p;
	Dog *d;
	string name, breed;
	int weight, num;
	cout << "Enter your pet's name: ";
	cin >> name;	
	p.setName(name);
	cout << "Enter your pet's weight(lbs): ";
	cin >> weight;
	p.setWeight(weight);
	cout << p.getLifespan() << endl;
	cout << "Enter number of dogs: ";
	cin >> num;
	d = new Dog[num];
	for (int i = 0; i < num; i++) {
		cout << "Enter your dog " << i+1 << "'s name: ";
		cin >> name;
		d[i].setName(name); 
		cout << "Breed: ";
		cin >> breed;
		d[i].setBreed(breed);
		cout << "Weight: ";
		cin >> weight;
		d[i].setWeight(weight);
		cout << "========================" << endl;
	}	
	for (int i = 0; i < num; i++) {
		cout << "lifespan for dog " << i+1 << ": " << d[i].getLifespan() << endl;
	}

	delete [] d;












	return 0;
}
