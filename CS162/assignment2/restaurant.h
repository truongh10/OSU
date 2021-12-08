/******************************************************
 * ** Program: restaurant.h
 * ** Author: Hao Truong
 * ** Date: 04/28/2019
 * ** Description: restaurant class 
 * ** Input: none
 * ** Output: none
 * ******************************************************/

#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <iostream>
#include "menu.h" //menu includes pizza...

using namespace std;

class Restaurant {
	private:
		Menu menu;
		employee* employees;
		hours* week;
		int num_day;
		string name;
		string phone;
		string address;
	public:
		
		Restaurant();
		~Restaurant();
		Restaurant(const Restaurant&);
		Restaurant& operator =(const Restaurant&);

};

#endif




















