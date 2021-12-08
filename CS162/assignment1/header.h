/*
Program: spellbooks and wizards
description: header file
Date: 01/14/19
Input: depends on functions
Output: depends on functions
*/
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std;

struct wizard {
        string name;
        int id;
        string password;
        string position_title;
        float beard_length;
};
struct spell {
        string name;
        float success_rate;
        string effect;
};
struct spellbook {
        string title;
        string author;
        int num_pages;
        int edition;
        int num_spells;
        float avg_success_rate;
        struct spell *s;
};

wizard *create_wizard(int);
void get_spellbook_data(spellbook *s, int, ifstream &);
int check_int(string);
void ask_id_password(wizard *,int,wizard *);
spellbook *create_spellbooks(int);
spell *create_spells(int);
void get_spell_data(spell *, int, ifstream &);
void get_spellbook_data(spellbook *, int, ifstream &);
void teacher_avg_success(spellbook *, int);
void student_avg_success(spellbook *, int);
void sort_by_numPages(spellbook *, int);
void sort_by_effect(spellbook *, int);
void sort_by_effect1(spellbook *, int);
void sort_by_avg(spellbook *, int);
void print_write_pages(spellbook *, int);
void print_write_pages1(spellbook *, int);
void delete_data(wizard **, spellbook **, int);
void print_options(wizard *,spellbook *, int);
void print_options(wizard *,spellbook *, int);






