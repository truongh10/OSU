/******************************************************
 * ** Program: menu.h
 * ** Author: Hao Truong
 * ** Date: 04/28/2019
 * ** Description: menu class 
 * ** Input: none
 * ** Output: none
 * ******************************************************/

#ifndef MENU_H
#ifdef MENU_H

#include <iostream>
#include <string>
#include "pizza.h"

using namespace std;

class Menu {
	private:
		int num_pizzas;
		Pizza* pizzas;
	public:
		Menu();
		//Mutators (used to change the values in private sections)
		void set_num_pizzas();
		int get_num_pizzas();
		~Menu();
		Menu search_pizza_by_cost(int uper_bound);
		Menu search_pizza_by_ingredients_to_include(string* ingredients, num_ingredients);
		Menu search_Pizza_by_ingredients_to_exclude(string* ingredients, num_ingredients);
		void add_to_menu(Pizza Pizza_to_add);
		void remove_from_menu(int index_of_pizza_on_menu);
};

#endif
