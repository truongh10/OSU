/******************************************************
 * ** Program: menu.h
 * ** Author: Hao Truong
 * ** Date: 04/28/2019
 * ** Description: functions for menu class 
 * ** Input: none
 * ** Output: none
 * ******************************************************/


#include <iostream>
#include <string>
#include <fstream>
#include "menu.h"
#include "pizza.h"

using namespace std;

Menu::Menu() {
	num_pizzas= get_num_pizzas();;
	Pizzas = new Pizza[num_pizza];
}

~Menu::Menu() {
	delete [] Pizzas;
}

void Menu::set_num_pizzas() {
	ifstream menu_file;
	int pizza_num=0;
	string line;
	pizza_file.open("menu.txt");
	
	if (!pizza_file.is_open()) {
		cout << "Error! Unable to open file menu.txt" << endl;
		exit(1);
	}
	while (getline(pizza_file,line)){
		pizza_num++;
	}
	num_pizzas = pizza_num;
}

int Menu::get_num_pizzas() {
	return num_pizzas;
}

Menu::Menu(const Restaurant& other) {
	num_pizzas = other.num_pizzas;
	if(num_Pizzas >0) {
		Pizzas = new Pizza[num_pizzas];
		for(int i=0; i<num_pizzas; i++) {
			Pizzas[i] = other.Pizzas[i];
		}
	}
}


Menu& Menu::operator = (const Menu& other) {
	delete [] Pizzas;
	num_pizzas = other.num_pizzas;
	if(num_Pizzas >0) {
		Pizzas = new Pizza[num_pizzas];
		for(int i=0; i<num_pizzas; i++) {
			Pizzas[i] = other.Pizzas[i];
		}
	}
}















