#include <iostream>

using namespace std;

	struct node{
		int val;
		struct node* next;
	};

class LinkedList{

	struct node* root;

	public:

	// Constructor for the LinkedList
	LinkedList() {
		root = NULL;
	}

	// Function to insert a new value at the beginning of the LinkedList
	void insertFront(int data) {
		if(root == NULL) {
			node* cur = new node();;
			cur->val = data;
			cur->next = NULL;
			root = cur;
		}
		else {
			node* cur = new node();
			cur->val = data;
			cur->next = root;
			root = cur;
		}
	}

	// Function to insert an element at the back of a linkedlist
	void insertBack(int data) {
		if(root == NULL) {
			node* cur = new node();
			cur->val = data;
			cur->next = NULL;
			root = cur;
		}
		else {
			node* tmp = new node();
			tmp->val = data;
			tmp->next = NULL;
			node* cur = new node();
			cur = root;
			while(cur!=NULL){
				if(cur->next == NULL) {
					cur->next = tmp;
					break;
				}
				cur = cur->next;
			}
		}
	}

	// Function to print out the contents of the Linked List
	void printList() {
		if (root == NULL) {
			cout << "List is empty!" << endl;
		}
		else {
			node* cur = new node();
			cur = root;
			while(cur != NULL) {
				cout << cur->val << endl;
				cur = cur->next;
			}
		}
	}

};

int main(){
	cout <<"Hello sidd" << endl;
	LinkedList list1;
	list1.insertFront(1);
	list1.insertFront(2);
	list1.insertFront(3);
	list1.insertBack(0);
	list1.insertFront(4);
	list1.insertBack(-1);
	list1.printList();
}