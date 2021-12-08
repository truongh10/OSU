/******************************************************
 * ** Program: employee_hours_struct
 * ** Author: Hao Truong
 * ** Date: 04/28/2019
 * ** Description: structs of employee and hours 
 * ** Input: none
 * ** Output: none
 * ******************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "pizza.h"
#include "employee_hours.h"
#include "menu.h"
#include "restaurant.h"

using namespace std;

struct employee {
	int id;
	string password;
	string first_name;
	string last_name;
};

struct hours {
	string day;
	string open_hour;
	string close_hour;
};


int employee_file();
employee *create_employee(int num_employees);
void employees_ (employee* employees, int num_employees, ifstream read_employee);
void employee_data(employee *employees, int num_employees, ifstream &read_employee);
void welcome_display(employee* employees, int num_employees);
void ask_for_id_password(employee* employees, int num_employees, employee* employee_info);
void employee_login_display(employee* employees, int ID, int num_employees, string user_password);


