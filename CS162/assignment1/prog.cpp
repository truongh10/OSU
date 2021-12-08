
/*PROGRAM: SPELLBOOKS AND WIZARDS
 * DESCRIPTION: functions
 * DATE:04/14/19
 * INPUT:DEPENDS ON FUNCTIONS
 * OUTPUT:DEPENDS ON FUNTIONS
 * */
#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include "header.h"

using namespace std;

wizard *create_wizard(int num_wizards);
void get_wizard_data(wizard *wizard_info, int read, ifstream &read_wizard);
int check_int(string s);
void ask_id_password(wizard *wizard_info, int num_wizards, wizard *wizard_title);
spellbook *create_spellbooks(int num_spellbooks);
spell *create_spells(int spells);
void get_spell_data(spell *spells_info, int spells, ifstream &read_spellbooks);
void get_spellbook_data(spellbook *spellbooks_info, int num_spellbooks, ifstream &read_spellbooks);
void teacher_avg_success(spellbook *spellbooks_info, int num_spellbooks);
void student_avg_success(spellbook *spellbooks_info, int num_spellbooks);
void sort_by_numPages(spellbook *spellbooks_info, int num_spellbooks);
void sort_by_effect(spellbook *spellbooks_info, int num_spellbooks);
void sort_by_effect1(spellbook *spellbooks_info, int num_spellbooks);
void print_write_pages(spellbook *spellbooks_info, int num_spellbooks);
void print_write_pages1(spellbook *spellbooks_info, int num_spellbooks);
void delete_data(wizard **wizard_info, spellbook **spellbooks_info, int num_spellbooks);
void print_options(wizard *wizard_info,spellbook *spellbooks_info, int num_spellbooks);
void print_options1(wizard *wizard_info,spellbook *spellbooks_info, int num_spellbooks);
 



wizard *create_wizard(int num_wizards) {
	wizard *wizard_info = new wizard[num_wizards];
	return wizard_info;
}

//read wizard text file
void get_wizard_data(wizard *wizard_info, int read, ifstream &read_wizard){
	for (int i=0; i<read; i++) {
		read_wizard >> wizard_info[i].name;
		read_wizard >> wizard_info[i].id;
		read_wizard >> wizard_info[i].password;
		read_wizard >> wizard_info[i].position_title;
		read_wizard >> wizard_info[i].beard_length;
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
//ask for ID and password
void ask_id_password(wizard *wizard_info, int num_wizards, wizard *wizard_title) {
	string id, user_password;
	int user_id = 0, chance=0;
	bool check1;
	do {
		++chance;
		cout << "Enter ID: ";
		getline(cin, id);
		user_id = check_int(id);
		cout << "Enter your password: ";
		getline(cin,user_password);
	
		for (int i=0; i<num_wizards; i++) {
			if (user_id == wizard_info[i].id && user_password == wizard_info[i].password) {
				cout << "Welcome " << wizard_info[i].name << endl;
				cout << "ID: " << wizard_info[i].id << endl;
				cout << "Status: " << wizard_info[i].position_title << endl;
				cout << "Beard Length: " << wizard_info[i].beard_length << endl;
				check1 = true;
				*wizard_title = wizard_info[i];
			}
		}
		if ((check1 != true) && (chance < 3)) {
			cout << "Either your ID or password is not correct. Enter again" << endl;
		}
		else if ((check1 != true) && (chance == 3)){
			 exit(1);
		}
	}while(check1 == false);
}

spellbook *create_spellbooks(int num_spellbooks) {
	spellbook * spellbooks_info = new spellbook[num_spellbooks];
	return spellbooks_info;
} 

spell *create_spells(int spells) {
	spell *spells_info = new spell[spells];
	return spells_info;
}

void get_spell_data(spell *spells_info, int spells, ifstream &read_spellbooks) {
        for (int j=0; j<spells; j++) {
                read_spellbooks >> spells_info[j].name;
                read_spellbooks >> spells_info[j].success_rate;
                read_spellbooks >> spells_info[j].effect;
        }                
}


//read spellbooks.txt file into struct
void get_spellbook_data(spellbook *spellbooks_info, int num_spellbooks, ifstream &read_spellbooks) {
	for (int i=0; i<num_spellbooks; i++) {
		read_spellbooks >> spellbooks_info[i].title;
		read_spellbooks >> spellbooks_info[i].author;
		read_spellbooks >> spellbooks_info[i].num_pages;
		read_spellbooks >> spellbooks_info[i].edition;
		read_spellbooks >> spellbooks_info[i].num_spells;
		spellbooks_info[i].s = create_spells(spellbooks_info[i].num_spells);
		get_spell_data(spellbooks_info[i].s, spellbooks_info[i].num_spells, read_spellbooks);
		float avg_success = 0;
		for (int j=0; j< spellbooks_info[i].num_spells; j++) {
			avg_success += spellbooks_info[i].s[j].success_rate;
		}
		spellbooks_info[i].avg_success_rate = (avg_success/spellbooks_info[i].num_spells);
	}
}

//calculating avg success rate for teachers/masters
void teacher_avg_success(spellbook *spellbooks_info, int num_spellbooks) {
	for(int i=0; i< num_spellbooks-1; i++) {
		for (int j =0; j<num_spellbooks-i-1; j++) {
			if (spellbooks_info[j].avg_success_rate <spellbooks_info[j+1].avg_success_rate) {
				spellbook tmp = spellbooks_info[j];
				spellbooks_info[j] = spellbooks_info[j+1];
				spellbooks_info[j+1] = tmp;
			}
		}
	}
	cout << "\nHow would you want your information displayed?" << endl;
	cout << "Print to screen (Press 1)" << endl;
        cout << "Print to a file (Press 2)" << endl;
	int choice = 0;
	string input;
	getline(cin,input);
        choice = check_int(input);
        switch (choice) {
		case 1:	{
			for (int i =0; i<num_spellbooks; i++) {
				cout << spellbooks_info[i].title << " " << spellbooks_info[i].avg_success_rate << endl;
			}
		}
		break;
		case 2: {
			string filename;
                        ofstream file_input;
                        cout << "Please Provide desired filename: ";
                        getline(cin,filename);
                        file_input.open(filename.c_str());
                        for (int i = 0; i < num_spellbooks; i++) {
                                file_input << spellbooks_info[i].title << " " << spellbooks_info[i].avg_success_rate << endl;
                        }
                        cout << "Appended requested information to file!" << endl;
		}
		break;
		default: break;
	}
}

//calculating avg success rate for students
void student_avg_success(spellbook *spellbooks_info, int num_spellbooks) {
        for(int i=0; i< num_spellbooks-1; i++) {
                for (int j =0; j<num_spellbooks-i-1; j++) {
                        if (spellbooks_info[j].avg_success_rate <spellbooks_info[j+1].avg_success_rate) {
                                spellbook tmp = spellbooks_info[j];
                                spellbooks_info[j] = spellbooks_info[j+1];
                                spellbooks_info[j+1] = tmp;
                        }
                }
        }
        cout << "\nHow would you want your information displayed?" << endl;
        cout << "Print to screen (Press 1)" << endl;
        cout << "Print to a file (Press 2)" << endl;
        int choice = 0;
        string input;
        getline(cin,input);
        choice = check_int(input);
	switch (choice) {
                case 1: {
                        for (int i = 0; i < num_spellbooks; i++) {
                                bool check = true;
                                for (int j = 0; j < spellbooks_info[i].num_spells; j++) {
                                        if (spellbooks_info[i].s[j].effect == "poison" || spellbooks_info[i].s[j].effect == "death") {
                                                check = false;
                                                break;
                                        }
                                }
                                if (check)
                                cout << spellbooks_info[i].title << " " << spellbooks_info[i].avg_success_rate << endl;
                        }
                }
                        break;
                case 2: {
                        string filename;
                        ofstream file_input;
                        cout << "Please Provide desired filename: ";
                        getline(cin,filename);
                        file_input.open(filename.c_str());
                        for (int i = 0; i < num_spellbooks; i++) {
                                bool check = true;
                                for (int j = 0; j < spellbooks_info[i].num_spells; j++) {
                                        if (spellbooks_info[i].s[j].effect == "poison" || spellbooks_info[i].s[j].effect == "death") {
                                                check = false;
                                                break;
                                        }
                                }
                                if (check)
                                        file_input << spellbooks_info[i].title << spellbooks_info[i].avg_success_rate << endl;
                        }
                        cout << "Appended requested information to file." << endl;
                }
                        break;
                default:
                        break;
        }

}


//sort spellbooks by number of pages
void sort_by_numPages(spellbook *spellbooks_info, int num_spellbooks) {
	for (int i=0; i < num_spellbooks-1; i++) {
		for (int j=0; j< num_spellbooks-i-1; j++) {
			if (spellbooks_info[j].num_pages > spellbooks_info[j+1].num_pages) {
				spellbook tmp = spellbooks_info[j+1];
				spellbooks_info[j+1] = spellbooks_info[j];
				spellbooks_info[j] = tmp;
			}
		}
	}
}

//sort spells by effect for teachers
void sort_by_effect(spellbook *spellbooks_info, int num_spellbooks) {
	int choice = 0;
        string input;
        cout << "\nHow would you like the information displayed?" << endl;
        cout << "Print to screen (Press 1)" << endl;
        cout << "Print to a file (Press 2)" << endl;

        getline(cin,input);
        choice = check_int(input);
	switch (choice) {
	case 1: {
		for (int i = 0; i < num_spellbooks; i++) {
			for (int j = 0; j < spellbooks_info[i].num_spells; j++) {
				if (spellbooks_info[i].s[j].effect.compare("bubble") == 0) {
					cout <<  spellbooks_info[i].s[j].effect << " " << spellbooks_info[i].s[j].name << endl;
				}
			}
		}
		for (int i = 0; i < num_spellbooks; i++) {
			for (int j = 0; j < spellbooks_info[i].num_spells; j++) {
				if (spellbooks_info[i].s[j].effect.compare("memory_loss") == 0) {
					cout << spellbooks_info[i].s[j].effect << " " << spellbooks_info[i].s[j].name << endl;
				}
			}
		}
		for (int i = 0; i < num_spellbooks; i++) {
			for (int j = 0; j < spellbooks_info[i].num_spells; j++) {
				if (spellbooks_info[i].s[j].effect.compare("fire") == 0) {
					cout << spellbooks_info[i].s[j].effect << " " << spellbooks_info[i].s[j].name << endl;
				}
			}
		}
		for (int i = 0; i < num_spellbooks; i++) {
			for (int j = 0; j < spellbooks_info[i].num_spells; j++) {
				if (spellbooks_info[i].s[j].effect.compare("poison") == 0) {
					cout << spellbooks_info[i].s[j].effect << " " << spellbooks_info[i].s[j].name << endl;
				}
			}
		}
		for (int i = 0; i < num_spellbooks; i++) {
			for (int j = 0; j < spellbooks_info[i].num_spells; j++) {
				if (spellbooks_info[i].s[j].effect.compare("death") == 0) {
					cout << spellbooks_info[i].s[j].effect << " " << spellbooks_info[i].s[j].name << endl;
				}
			}
		}
	}
		break;
	case 2: {
		string filename;
                ofstream file_input;
                cout << "Please Provide desired filename: ";
                getline(cin,filename);
                file_input.open(filename.c_str());
		for (int i = 0; i < num_spellbooks; i++) {
                        for (int j = 0; j < spellbooks_info[i].num_spells; j++) {
                                if (spellbooks_info[i].s[j].effect.compare("bubble") == 0) {
                                       file_input <<  spellbooks_info[i].s[j].effect << " " << spellbooks_info[i].s[j].name << endl;
                                }
                        }
                }
                for (int i = 0; i < num_spellbooks; i++) {
                        for (int j = 0; j < spellbooks_info[i].num_spells; j++) {
                                if (spellbooks_info[i].s[j].effect.compare("memory_loss") == 0) {
                                        file_input << spellbooks_info[i].s[j].effect << " " << spellbooks_info[i].s[j].name << endl;
                                }
                        }
                }
                for (int i = 0; i < num_spellbooks; i++) {
                        for (int j = 0; j < spellbooks_info[i].num_spells; j++) {
                                if (spellbooks_info[i].s[j].effect.compare("fire") == 0) {
                                        file_input << spellbooks_info[i].s[j].effect << " " << spellbooks_info[i].s[j].name << endl;
                                }
                        }
                }
                for (int i = 0; i < num_spellbooks; i++) {
                        for (int j = 0; j < spellbooks_info[i].num_spells; j++) {
                                if (spellbooks_info[i].s[j].effect.compare("poison") == 0) {
                                        file_input << spellbooks_info[i].s[j].effect << " " << spellbooks_info[i].s[j].name << endl;
                                }
                        }
                }
                for (int i = 0; i < num_spellbooks; i++) {
                        for (int j = 0; j < spellbooks_info[i].num_spells; j++) {
                                if (spellbooks_info[i].s[j].effect.compare("death") == 0) {
                                        file_input << spellbooks_info[i].s[j].effect << " " << spellbooks_info[i].s[j].name << endl;
                                }
                        }
                }
	}
		break;
	default:
		break;
	}
}

//sort by effect for students
void sort_by_effect1(spellbook *spellbooks_info, int num_spellbooks) {
        int choice = 0;
        string input;
        cout << "\nHow would you like the information displayed?" << endl;
        cout << "Print to screen (Press 1)" << endl;
        cout << "Print to a file (Press 2)" << endl;

        getline(cin,input);
        choice = check_int(input);
        switch (choice) {
        case 1: {
                for (int i = 0; i < num_spellbooks; i++) {
                        for (int j = 0; j < spellbooks_info[i].num_spells; j++) {
                                if (spellbooks_info[i].s[j].effect.compare("bubble") == 0) {
                                        cout <<  spellbooks_info[i].s[j].effect << " " << spellbooks_info[i].s[j].name << endl;
                                }
                        }
                }
                for (int i = 0; i < num_spellbooks; i++) {
                        for (int j = 0; j < spellbooks_info[i].num_spells; j++) {
                                if (spellbooks_info[i].s[j].effect.compare("memory_loss") == 0) {
                                        cout << spellbooks_info[i].s[j].effect << " " << spellbooks_info[i].s[j].name << endl;
                                }
                        }
                }
                for (int i = 0; i < num_spellbooks; i++) {
                        for (int j = 0; j < spellbooks_info[i].num_spells; j++) {
                                if (spellbooks_info[i].s[j].effect.compare("fire") == 0) {
                                        cout << spellbooks_info[i].s[j].effect << " " << spellbooks_info[i].s[j].name << endl;
                                }
                        }
                }
	}
		break;
	case 2: {
                string filename;
                ofstream file_input;
                cout << "Please Provide desired filename: ";
                getline(cin,filename);
                file_input.open(filename.c_str());
                for (int i = 0; i < num_spellbooks; i++) {
                        for (int j = 0; j < spellbooks_info[i].num_spells; j++) {
                                if (spellbooks_info[i].s[j].effect.compare("bubble") == 0) {
                                       file_input <<  spellbooks_info[i].s[j].effect << " " << spellbooks_info[i].s[j].name << endl;
                                }
                        }
                }
                for (int i = 0; i < num_spellbooks; i++) {
                        for (int j = 0; j < spellbooks_info[i].num_spells; j++) {
                                if (spellbooks_info[i].s[j].effect.compare("memory_loss") == 0) {
                                        file_input << spellbooks_info[i].s[j].effect << " " << spellbooks_info[i].s[j].name << endl;
                                }
                        }
                }
                for (int i = 0; i < num_spellbooks; i++) {
                        for (int j = 0; j < spellbooks_info[i].num_spells; j++) {
                                if (spellbooks_info[i].s[j].effect.compare("fire") == 0) {
                                        file_input << spellbooks_info[i].s[j].effect << " " << spellbooks_info[i].s[j].name << endl;
                                }
                        }
                }
	}
		break;
	default: break;
	}
}
//sort by average success rate
void sort_by_avg(spellbook *spellbooks_info, int  num_spellbooks) {
	for (int i = 0; i < num_spellbooks-1; i++) {
		for (int j = 0; j < num_spellbooks-i-1; j++) {
			if(spellbooks_info[j].avg_success_rate < spellbooks_info[j+1].avg_success_rate) {
				spellbook tmp = spellbooks_info[j];
				spellbooks_info[j] = spellbooks_info[j+1];
				spellbooks_info[j+1] = tmp;
			}
		}
	}
}

//ASking if the user(teacher) wants the information printed to the screen or written to a file
void print_write_pages(spellbook *spellbooks_info, int num_spellbooks) {
	int choice = 0;
	string input;
	cout << "\nHow would you like the information displayed?" << endl;
	cout << "Print to screen (Press 1)" << endl;
	cout << "Print to a file (Press 2)" << endl;
	
	getline(cin,input);
	choice = check_int(input);
	switch (choice) {
		case 1: {
			for (int i = 0; i < num_spellbooks; i++) {
			cout << spellbooks_info[i].title << " " << spellbooks_info[i].num_pages << endl;
			}
		}
			break;
		
		case 2: {
			string filename;
			ofstream file_input;
			cout << "Please Provide desired filename: ";
			getline(cin,filename);
			file_input.open(filename.c_str());
			for (int i = 0; i < num_spellbooks; i++) {
				file_input << spellbooks_info[i].title << " " << spellbooks_info[i].num_pages << endl;
			} 
			cout << "Appended requested information to file!" << endl;
			}
			break;
		
		default:
			cout << "Sorry, Invalid input" << endl;
			break;	
	}
}

//ASking if the user(student) wants the information printed to the screen or written to a file
void print_write_pages1(spellbook *spellbooks_info, int num_spellbooks) {
        int choice = 0;
        string input;
        cout << "\nHow would you like the information displayed?" << endl;
        cout << "Print to screen (Press 1)" << endl;
        cout << "Print to a file (Press 2)" << endl;

        getline(cin,input);
        choice = check_int(input);
        switch (choice) {
                case 1: {
                        for (int i = 0; i < num_spellbooks; i++) {
				bool check = true;
				for (int j = 0; j < spellbooks_info[i].num_spells; j++) {
					if (spellbooks_info[i].s[j].effect == "poison" || spellbooks_info[i].s[j].effect == "death") {
						check = false;
						break;
					}
				}
				if (check)
                        	cout << spellbooks_info[i].title << " " << spellbooks_info[i].num_pages << endl;
			}
		}
               		break;
		case 2: {
			string filename;
                        ofstream file_input;
                        cout << "Please Provide desired filename: ";
                        getline(cin,filename);
                        file_input.open(filename.c_str());
			for (int i = 0; i < num_spellbooks; i++) {
                                bool check = true;
                                for (int j = 0; j < spellbooks_info[i].num_spells; j++) {
                                        if (spellbooks_info[i].s[j].effect == "poison" || spellbooks_info[i].s[j].effect == "death") {
                                                check = false;
                                                break;
                                        }
                                }
                                if (check)
					file_input << spellbooks_info[i].title << spellbooks_info[i].num_pages << endl;
			}
			cout << "Appended requested information to file." << endl;
		}
			break;
		default:
			break;
        }
}

void delete_data(wizard **wizard_info, spellbook **spellbooks_info, int num_spellbooks) {
        delete [] *wizard_info;
        *wizard_info = NULL;

        for (int i=0; i<num_spellbooks; i++) {
                delete [] (*spellbooks_info)[i].s;
                (*spellbooks_info)[i].s=NULL;
        }
        delete [] *spellbooks_info;
        *spellbooks_info = 0;
}


//asking how the user(teacher) wants the information sorted)
void print_options(wizard *wizard_info,spellbook *spellbooks_info, int num_spellbooks) {
	int choice=0;
	string input;
		cout << "\nWhich options would you like to choose?" << endl;
		cout << "Sort spellbooks by number of pages (Press 1):" << endl;
		cout << "Group spells by their effect (Press 2):" << endl;
		cout << "Sort spellbooks by average success rate (Press 3):" << endl;
		cout << "Quit (Press 4):" << endl;

		getline(cin,input);
		choice = check_int(input);
		switch (choice) {
			case 1: {
				sort_by_numPages(spellbooks_info,num_spellbooks);
				print_write_pages(spellbooks_info,num_spellbooks);
			}
				break;
			case 2:	{
				sort_by_effect(spellbooks_info,num_spellbooks);
			}
				break;
			case 3: {
				teacher_avg_success(spellbooks_info,num_spellbooks);
			}
				break;
			case 4: {
				delete_data(&wizard_info,&spellbooks_info,num_spellbooks);
				cout << "GOOD BYE!" << endl;
				exit(1);
			}
				break;
			default:
				break;		
				
		}
}

//display options for students
void print_options1(wizard *wizard_info,spellbook *spellbooks_info, int num_spellbooks) {
        int choice=0;
        string input;
                cout << "\nWhich options would you like to choose?" << endl;
                cout << "Sort spellbooks by number of pages (Press 1):" << endl;
                cout << "Group spells by their effect (Press 2):" << endl;
                cout << "Sort spellbooks by average success rate (Press 3):" << endl;
                cout << "Quit (Press 4):" << endl;

                getline(cin,input);
                choice = check_int(input);
                switch (choice) {
                        case 1: {
                                sort_by_numPages(spellbooks_info,num_spellbooks);
                                print_write_pages1(spellbooks_info,num_spellbooks);
                        }
                                break;
                        case 2: {
                                sort_by_effect1(spellbooks_info,num_spellbooks);
                        }
                                break;
                        case 3: {
                                student_avg_success(spellbooks_info,num_spellbooks);
                        }
                                break;
                        case 4: {
				delete_data(&wizard_info,&spellbooks_info,num_spellbooks);
                                cout << "GOOD BYE!" << endl;
                                exit(1);
                        }
                                break;
                        default:
                                break;

                }
}





