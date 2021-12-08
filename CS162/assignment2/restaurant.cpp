/******************************************************
 * ** Program: restaurant.cpp
 * ** Author: Hao Truong
 * ** Date: 04/28/2019
 * ** Description: functions for restaurant class
 * ** Input: none
 * ** Output: none
 * ******************************************************/

#include <iostream>
#include <string>
#include "restaurant.h"

using namespace std;

Restaurant::Restaurant() {
	name = "";
	phone = "";
	address = "";
	num_day=7;
	week = new hours[num_day];
}

Restaurant::~Restaurant() {
	if (week != NULL) {
		delete [] week;
	}
}

//copy constructor
Restaurant::Restaurant(const Restaurant & other) {
	num_day = other.num_day;
	if(num_day > 0) {
		week = new hours[num_day];
		for (int i=0; i<num_day; i++) {
			week[i] = other.week[i];
		}
	}
}

//assignment operator overload
Restaurant& Restaurant::operator =(const Restaurant& other) {
	if (week != NULL) {
		delete [] week;
	}
	num_day = other.num_day;
//	week = other.week;
	if(num_day > 0) {
		week = new hours[num_day];
		for (int i=0; i<num_day; i++) {
			week[i] = other.week [i];
		}
	}	
}


