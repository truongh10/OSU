#include <iostream>
#include <string>
#include <fstream>
#include "pizza.h"

using namespace std;


Pizza::Pizza() {
   Pizza *pizza_arr = new Pizza[]
}

void Pizza::set_name(string name) {
   this->name = name;
}

string Pizza::get_name() {
   return name;
}

void Pizza::set_num_ingredients(int num){
   num_ingredients = num;
}

int Pizza::get_num_ingredients() {
   return num_ingredients;
}




int main() {
   Pizza *pizza_arr;   

   iftream restaurant;
   restaurant.open("restaurant_info.txt");
   string restaurant_name;
   restaurant >> restaurant_name;
   return 0;
}
