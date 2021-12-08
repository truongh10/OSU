#include <iostream>
#include <string>

using namespace std;

struct student { // struct name is "student"

	int id;
	string first_name;
	string last_name;
	string major;
};


student* make_student_database(int);
void student_data(student *, int, ifstream &);
void delete_info(student *, int);
void sorting_id(student *, int);
void sorting_last(student *, int);
void sorting_major(student *, int);
