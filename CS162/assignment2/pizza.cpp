/******************************************************
 * ** Program: pizza.cpp
 * ** Author: Hao Truong
 * ** Date: 04/28/2019
 * ** Description: functions for pizza class 
 * ** Input: none
 * ** Output: none
 * ******************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "pizza.h"
using namespace std;

//constructor
Pizza::Pizza() {
	name = "";
	num_ingredients = 0;
	ingredients = 0;
}

void Pizza::read_file(ifstream &menu_file) {
		file >> name >> small_cost >> medium_cost >> large_cost >> num_ingredients;
	
		ingredients = new string[num_ingredients];

		for (int i = 0 ; i < num_ingredients; i++) {
			file >> ingredients[i];
		}
	}
	file.close();
}

void Pizza::set_name(string name){
	this->name = name;
}

string Pizza::get_name() {
	return name;
}

void Pizza::set_num_ingredients(int num) {
	num_ingredients = num;
}

int Pizza::get_num_ingredients() {
	return num_ingredients;
}


Pizza::~Pizza() {
	if (week != NULL) {
		delete [] ingredients;
	}
}

//copy constructor
Pizza::Pizza(const Pizza & other) {
	num_ingredients = other.num_ingredients;
	if(num_ingredients > 0) {
		ingredients = new string[num_ingredients];
		for (int i=0; i<num_ingredients; i++) {
			ingredients[i] = other.ingredients[i];
		}
	}
}

//assignment operator overload
Pizza& Pizza::operator =(const Pizza& other) {
	if (week != NULL) {
		delete [] week;
	}
	num_ingredients = other.num_ingredients;
	if(num_ingredients > 0) {
		ingredients = new string[num_ingredients];
		for (int i=0; i<num_ingredients; i++) {
			ingredients[i] = other.ingredients[i];
		}
	}
}


