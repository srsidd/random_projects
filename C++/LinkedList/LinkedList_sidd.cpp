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
					cout << data <<" found at " << counter << "th position in the list" << endl;
					return;
				}
				counter++;
				cur = cur->next;
			}
			cout << data << " not present in the list" << endl;
		}
	}

	// Function to display the kth element of the list
	void getKth(int k) {
		node* cur = new node();

		int counter = 0;

		cur = root;

		while(cur != NULL) {
			if(counter == k) {
				cout << "The " << k << "th element is " << cur->val << endl;
				return;
			}
			cur = cur->next;
			counter++;
		}
		cout << "The value of k " << k << " is bigger than the size of the list" << endl;
	}


	// Function to display kth element from the back of the linked list
	void getKthFromBack(int k) {
		node* first = new node();
		node* second = new node();

		first = root;
		second = root;

		int cntr = 0;

		if (k < 0) {
			cout << "K is not a valid number" << endl;
			return;
		}

		while(first != NULL) {
			first = first->next;
			if (cntr > k) {
				second = second-> next;
			}
			cntr++;
		}
		if(k > cntr) {
			cout << "The value of k " << k << " is bigger than the size of the list, " << cntr << endl;
		}
		else {
			cout << "The " << k << "th element from the back is " << second->val << endl;
		}
	}

	// Function to count the number of times a given int occurs in a LinkedList
	void count(int k) {
		node* cur = new node();

		cur = root;

		int counter = 0;

		while(cur != NULL) {
			if(cur->val == k) {
				counter++;
			}
			cur = cur->next;
		}
		cout << "The frequency of " << k << " in the list is " << counter << endl;

	}

	// Function to delete the list
	void deleteList() {
		node* cur = new node();
		while(cur != NULL) {
			delete cur;
			cur = cur->next; 
		}
		root = NULL;
	}

	// Function to insert node at the nth position in the list
	void insertAtN(int n,int data) {
		node* cur = new node();
		int counter = 0;

		cur = root;

		while(cur != NULL) {
			if(counter == n-1) {
				node* temp = new node();
				temp->val = data;
				temp->next = cur->next;
				cur->next = temp;
				return;
			}
			if(cur->next == NULL) {
				cout << "The value of " << n << " is greater than the size of the list" << endl;
				node* temp = new node();
				temp->val = data;
				cur->next = temp;
				temp->next = NULL;
				return;
			}
			cur = cur->next;
			counter++;
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
	list1.searchList(0);
	list1.searchList(4);
	list1.getKthFromBack(30);
	list1.getKthFromBack(2);
	list1.getKthFromBack(1);
	list1.getKthFromBack(-1);
	list1.getKth(0);
	list1.getKth(1);
	list1.getKth(2);
	list1.getKth(33);
	list1.insertBack(-1);
	list1.insertBack(-1);
	list1.insertBack(-1);
	list1.insertFront(-1);
	list1.insertFront(-1);
	list1.insertFront(-1);
	list1.insertFront(-1);
	list1.printList();
	list1.count(100);
	list1.count(-1);
	list1.insertAtN(4, 100);
	list1.printList();
}