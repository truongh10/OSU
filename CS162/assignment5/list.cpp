/***************************************
 * Program: Linked List implementation
 * Date: 6/9/19
 * description: Linked_List cpp file
 * Inputs: number for each node, y/n
 * Output: Print list
 **************************************/

#include "list.h"
#include <cstdlib>

Linked_List::Linked_List() {
	length = 0;
	first = NULL;	
}

int Linked_List::get_length() {
	return length;
}

unsigned int Linked_List::push_front(int value) {
	Linked_List_Node *node = new Linked_List_Node;
	node->val = value;
	node->next = first;
	first = node;
	length++;
	return length;
}

unsigned int Linked_List::push_back(Linked_List_Node *node,int value) {
	node = new Linked_List_Node;
	Linked_List_Node *last = new Linked_List_Node;
	last = first;
	node->val = value;
	node->next = NULL;
	if (first == NULL) {
		first = node;
	}
	while (last->next != NULL) {
		last = last->next;
	}
	last->next = node;
	length++;
	return length;
}

unsigned int Linked_List::insert(int value, unsigned int index) {
	Linked_List_Node *current = first;
	int tmp_index = 0;
	
	if (index > length) {
		cout << "Given index is out of bound!" << endl;
		cout << "Node will be added at tail!" << endl;
		push_back(current,value);
	}
	else if (index <= length) {
		while (current->next != NULL && tmp_index != index) {
			current = current->next;
			tmp_index++;
		}
		if (index == 0) {
			cout << "Adding node at Head!" << endl;
			push_front(value);
		}
		else if (current->next == NULL && index == tmp_index) {
			cout << "Adding node at tail!" << endl;
			push_back(current,value);
		}
	}
}

void Linked_List::print() {
	Linked_List_Node *node = first;
	while (node != NULL) {
		cout << node->val << " ";
		first = node->next;
	}
	cout << endl;
}

void Linked_List::clear() {
	Linked_List_Node *current = first;
	while (current != NULL) {
		current = current->next;
		delete current;
		current = first;
	}
}

void Linked_List::merge(Linked_List_Node *head, int l, int m, int r) {
	int i,j,k;
	int n1 = m-l+1;
	int n2 = r-m;
	Linked_List_Node *L, *R;
	for(i=0; i < n1; i++) {
		L = head;
		L = L->next;
	}
	R = L->next;
	for(j=0; j <n2; j++) {
		R = R->next;
	}
	i = j = 0;
	k =l;
	while(i<n1 && j<n2) {
		if (L->val <= R->val) {
			head->val = L->val;
			L = L->next;
			i++;
		}
		else {
			head->val = R->val;
			R = R->next;
			j++;
		}
		k++;
	}
	while(i<n1) {
		head->val = L->val;
		L = L->next;
		i++, k++;
	}
	while (i<n2) {
		head->val = R->val;
		R = R->next;
		j++, k++;
	}


	
//	if (head1 ==NULL) 
//		return head2;
///	else if (head2 ==NULL)
//		return head1;
//	if (head1->val < head2->val) {
//		newHead = head1;
//		newHead->next = merge(head1->next, head2);
//	}
//	else {
//		newHead = head2;
//		newHead->next = merge(head1, head2->next);
//	}
	
}

void Linked_List::sort_ascending(Linked_List_Node *head, int l, int r) {
	if (l<r) {
		int m = l+(r-1)/2;
		sort_ascending(head,l,m);
		sort_ascending(head, m+1, r);
		merge(head,l,m,r);
	}
}

void Linked_List::ask_for_number(Linked_List_Node *head) {
	int num;
	char choice;
	int check = 1;
	cout << "Please Enter a number: ";
	cin >> num;
	push_back(head, num);
	while (check==1) {
		cout << "Do you want another num (y or n): ";
		cin >> choice;
		while (choice != 'y' && choice != 'n') {
			cout << "Invalid input! Enter again: ";
			cin >> choice;
		}
		if (choice == 'y') check = 1;
		else if (choice == 'n') check =0;
	}
	sort_ascending(head,0,length-1);
	cout << "Your list is: ";
	print();
	clear();
}




















