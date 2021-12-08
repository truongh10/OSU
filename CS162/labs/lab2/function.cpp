#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "header.h"

using namespace std;

student* make_student_database(int total_num_students) { //student is the struct

	student *database = new student[total_num_students]; // total number of students are 7
                                                        // database is pointing to total_num_students which is 7
                                                        //database

return database;
}

void student_data(student *data, int text, ifstream &student_info) {

		for (int i = 0; i < text; i++) {

			student_info >> data[i].id;
			student_info >> data[i].first_name;
			student_info >> data[i].last_name;
			student_info >> data[i].major;
		}

}

void delete_info(student *data, int text) {

	delete [] data;
}


void sorting_id(student *data, int total_num_students) {

	for (int i = 0; i < total_num_students-1; i++) {

		for (int j = 0; j < total_num_students-i-1; j++) {

			int tmp;

			if (data[j].id > data[j+1].id) {

				tmp = data[j+1].id;
				data[j+1].id = data[j].id;
				data[j].id = tmp;
			}
		}
	}
	for (int i = 0; i < total_num_students; i++) {
		cout << data[i].id << endl;
	}
}

void sorting_last(student *data, int total_num_students) {

	for (int i = 0; i < total_num_students-1; i++) {

		for (int j = 0; j < total_num_students-i-1; j++) {

			string tmp;

			if (data[j].last_name > data[j+1].last_name) {

				tmp = data[j+1].last_name;
				data[j+1].last_name = data[j].last_name;
				data[j].last_name = tmp;
			}

	 	}
  	}

	for (int i = 0; i < total_num_students; i++) {

		cout << data[i].last_name << endl;
	}
}

void sorting_major(student *data, int total_num_students) {

	for (int i = 0; i < total_num_students-1; i++) {

		for (int j = 0; j < total_num_students-i-1; j++) {

			string tmp;

			if (data[j].major > data[j+1].major) {

				tmp = data[j+1].major;
				data[j+1].major = data[j].major;
				data[j].major = tmp;
			}

	 	}
  	}

	for (int i = 0; i < total_num_students; i++) {

		cout << data[i].major << endl;

	}
}

