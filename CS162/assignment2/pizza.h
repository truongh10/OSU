/******************************************************
 * ** Program: pizza.h
 * ** Author: Hao Truong
 * ** Date: 04/28/2019
 * ** Description: pizza class 
 * ** Input: none
 * ** Output: none
 * ******************************************************/


#ifndef PIZZA_H
#define PIZZA_H

#include <iostream>
#include <string>

using namespace std;

class Pizza {
	private:
		string name;
		int small_cost;
		int medium_cost;
		int large_cost;
		int num_ingredients;
		string *ingredients;
	public:
		Pizza(); //default constructor
		//mutators
		void set_name(string name);
		void set_num_ingredients(int num);
		//accessors
		string get_name();
		int get_num_ingredients();

		void read_file();
};
#endif
