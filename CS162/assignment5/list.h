/***************************************
 * Program: Linked List implementation
 * Date: 6/9/19
 * description: Linked_List class
 * Inputs: none
 * Output: none
 **************************************/

#ifndef LIST_H
#define LIST_H

#include "node.h"

class Linked_List {
private:
	unsigned int length;
	Linked_List_Node *first;
public: 
	Linked_List();
	int get_length();
	void print();
	void clear();
	unsigned int push_front(int);
	unsigned int push_back(Linked_List_Node *,int);
	unsigned int insert(int val, unsigned int index);
	void merge(Linked_List_Node *, int, int,int);
	void sort_ascending(Linked_List_Node*, int, int);
	void sort_descending();
	void ask_for_number(Linked_List_Node*);
};
#endif
