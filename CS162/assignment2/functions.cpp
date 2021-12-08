
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "pizza.h"
#include "employee_hours.h"
#include "menu.h"
#include "restaurant.h"

using namespace std;

int employee_file();
employee *create_employee(int num_employees);
void employees_ (employee* employees, int num_employees, ifstream read_employee);
void employee_data(employee *employees, int num_employees, ifstream &read_employee);
void welcome_display(employee* employees, int num_employees);
void ask_for_id_password(employee* employees, int num_employees, employee* employee_info);
void employee_login_display(employee* employees, int ID, int num_employees, string user_password);

void employees_ (employee* employees, int num_employees, ifstream read_employee) {
	employees = create_employee(num_employees);
	employee_data(employees, num_employees,read_employee);
	read_employee.close();
}




employee *create_employee( int num_employees) {
	employee *employees_info = new employee[num_employees];
	return employees_info;
}

void employee_data(employee *employees, int num_employees, ifstream &read_employee) {
	for(int i=0; i<num_employees; i++) {
		read_employee >> employees[i].id;
		read_employee >> employees[i].password;
		read_employee >> employees[i].first_name;
		read_employee >> employees[i].last_name;
	}
}

int check_int(string s) {
	int integer;
	bool check;
	
	do {
		check = false;
		
		for (int i=0; i< s.length(); i++) {
			if (!(s.at(i) >= '0' && s.at(i) <= '9')) {
				cout << "Not a valid number. Enter again: ";
				getline(cin,s);
				check=true;
				break;
			}
		}
	}while(check);

	integer = atoi(s.c_str());
return integer;
}

void ask_for_id_password(employee* employees, int num_employees) {
	string user_id, user_password;
	int ID = 0;
	bool check1;

	do {
		cout << "Please enter your ID number: " << endl;
		cin.ignore();
		getline(cin,user_id);
		ID = check_int(user_id);
		cout << "Please enter your password" << endl;
		getline(cin, user_password);
		
		
		cout << num_employees << endl;
		for (int i=0; i<num_employees; i++) {
			if(ID == employees[i].id && user_password == employees[i].password) {
				cout << "Successgully logged in!" << endl;
				check1 = true;
				employee_login_display(employees,ID,num_employees,user_password);
			}
		}
		if (check1 != true) {
			int input;
			cout << "Incorrect ID or password. Would you like to try again (Press 1): ";
			cin >> input;
			if (input ==1) check1 = false;
			else {
				welcome_display(employees,num_employees);
				check1 = true;
			}		
		}	
	}while (check1 == false);
}

void employee_login_display(employee* employees, int ID, int num_employees, string user_password) {
	for (int i = 0; i < num_employees; i++) {
		if (ID == employees[i].id && user_password == employees[i].password) {
			cout << "Welcome " << employees[i].first_name << " " << employees[i].last_name << endl;
		}
	}
}

void welcome_display(employee* employees, int num_employees) {
	char input;
	

	cout << "Welcome to Bytes Pizza!" << endl;
	cout << "Are you a customer (C) or employee (E) or would you like to quit (Q)?";
	cin >> input;
	
	if(input == 'Q')
		exit(0);
	else if(input == 'C') {

	}
	else if(input == 'E') {	
		int check = 1;
		while (check ==1) {
			ask_for_id_password(employees,num_employees);
			
		}
	}
	else cout << "Invl";
}

