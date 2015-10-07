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

	// Function to search for an element in the Linked List
	void searchList(int data) {
		if (root == NULL) {
			cout << "List is emtpy!" << endl;
		}
		else {
			node* cur = new node();
			int counter = 0;
			cur = root;
			while(cur != NULL) {
				if(cur->val == data) {
					cout << "Item "<< data <<" found at " << counter << "th position in the list" << endl;
					return;
				}
				counter++;
				cur = cur->next;
			}
			cout << "Item " << data << " not present in the list" << endl;
		}
	}

	// Function to display kth element from the back of the linked list
	void getKthFromBack(int k) {
		node* first = new node();
		node* second = new node();

		first = root;
		second = root;

		int cntr = 0;

		while(first != NULL) {
			first = first->next;
			if (cntr > k) {
				second = second-> next;
			}
			cntr++;
		}
		cout << "The " << k << "th element is " << second->val << endl;
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
	list1.searchList(0);
	list1.searchList(4);
	list1.getKthFromBack(3);
	list1.getKthFromBack(2);
	list1.getKthFromBack(1);
	list1.getKthFromBack(0);
}