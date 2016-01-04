#include <iostream>
#include <string>

using namespace std;

struct node{
	int val;
	struct node* left;
	struct node* right;
};

class Tree{
	struct node* root;

public:
	Tree(){
		root = NULL;
	}

	void insert(int data) {
		if (root == NULL) {
			node* cur = new node();
			cur->val = data;
			cur->left = NULL;
			cur->right = NULL;
			root = cur;
		}
		else{
			node* cur = new node();
			cur = root;
			while(cur != NULL) {
				if(data < cur->val) {
					if(cur->left == NULL){
						node* tmp = new node();
						tmp->val = data;
						tmp->left = NULL;
						tmp->right = NULL;
						cur->left = tmp;
						break;
					}
					cur = cur->left;
				}
				else if(data > cur->val){
					if(cur->right == NULL){
						node* tmp = new node();
						tmp->val = data;
						tmp->left = NULL;
						tmp->right = NULL;
						cur->left = tmp;
						break;
					}
					cur = cur->right;
				}
			}
		}
	}
};


int main(){
	cout << "Hello Sidd" << endl;
	Tree tree1;
	tree1.insert(55);
	tree1.insert(54);
	tree1.insert(53);
}