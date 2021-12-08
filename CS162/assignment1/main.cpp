/*
Program: spellbooks and wizards
Description: main function
Input: depends on funtions
Output: depends on funtions
Date:
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
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



int main(int argc, char *argv[]){
	if(argc != 3){
		cout << "Not enough command line arguments! " << endl;
	return 1;
	}

	int num_wizards = 20, read;
	wizard wizard_title;
	ifstream read_wizard;// reads info from the file
	read_wizard.open("wizards.txt");
        if (!read_wizard.is_open()) {
                cout << "Error, unable to open file wizards.txt!" << endl;
                exit(1);
        }
	wizard *wizard_info;
	wizard_info = create_wizard(num_wizards);
	read_wizard >> read;
	get_wizard_data(wizard_info,read,read_wizard);
	read_wizard.close();
	ask_id_password(wizard_info, num_wizards, &wizard_title);
	

	ifstream read_spellbooks;
	read_spellbooks.open("spellbooks.txt");
	if (!read_spellbooks.is_open()) {
		cout << "Error, unable to open file spellbooks.txt!" << endl;
	}
	int num_spellbooks;
	read_spellbooks >> num_spellbooks;
	spellbook *spellbooks_info = create_spellbooks(num_spellbooks);
	spell *spells_info;
	get_spellbook_data(spellbooks_info,num_spellbooks,read_spellbooks);
	read_spellbooks.close();

	int check=1;
		if (wizard_title.position_title == "Headmaster" || wizard_title.position_title == "Teacher") {
			while (check ==1) {
			print_options(wizard_info,spellbooks_info,num_spellbooks);
			check =1;
			}
		}
	int check1=1;
		if (wizard_title.position_title == "Student") {
			while (check1=1) {
			print_options1(wizard_info,spellbooks_info,num_spellbooks);
			check1 =1;		
			}
		}
	return 0;
}
