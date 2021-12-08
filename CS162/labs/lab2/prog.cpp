#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "header.h"

using namespace std;

int main() {

	string file_enter;
	int total_num_students = 7;
	int text;

	ifstream student_info;
	student_info.open("student.txt");
	if (!student_info.is_open()) {

		cout << "Error opening the file" << endl;
		exit(1);
	}

	student *data = make_student_database(total_num_students);
	student_info >> text;

	student_data(data, text, student_info);

	cout << "Sorting students by ID" << endl;
        cout << endl;

	sorting_id(data, total_num_students);
	cout << endl;

	cout << "Sorting students by their Last Name" << endl;
        cout << endl;
	sorting_last(data, total_num_students);
	cout << endl;

	cout << "Sorting students by their Major Department" << endl;
        cout << endl;
	sorting_major(data, total_num_students);

	delete_info(data, text);

	student_info.close();

return 0;
}
