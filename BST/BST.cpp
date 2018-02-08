#include "BST.h"
#include <iostream>
#include <cstdlib>
using namespace std;


BST::BST() {
	root = NULL;
}
BST::Node* BST::CreateLeaf(int key) {
	Node* n = new Node;
	n->val = key;
	n->left = NULL;
	n->right = NULL;
	return n;
}
void BST::Insert_private(Node* ptr, int key) {
	if (root == NULL)
		root = BST::CreateLeaf(key);
	else if (key < ptr->val) {
		if (ptr->left != NULL)
			Insert_private(ptr->left, key);
		else
			ptr->left = CreateLeaf(key);
	}
	else if (key > ptr->val) {
		if (ptr->right != NULL)
			Insert_private(ptr->right, key);
		else
			ptr->right = CreateLeaf(key);
	}
}
void BST::Insert(int key) {
	BST::Insert_private(root, key);
}

void BST::PrintInOrder_private(Node* ptr) {
	if (ptr != NULL) {
		if (ptr->left != NULL)
			PrintInOrder_private(ptr->left);
		cout << ptr->val << " ";
		if (ptr->right != NULL)
			PrintInOrder_private(ptr->right);
	}
	else
		cout << "The Tree is empty\n";
}
void BST::PrintInOrder() {
	BST::PrintInOrder_private(root);
}

BST::Node* BST::Search_private(Node* ptr, int key) {
	if (ptr != NULL) {
		if (ptr->val == key)
			return ptr;
		else if (key < ptr->val)
			Search_private(ptr->left, key);
		else
			Search_private(ptr->right, key);
	}
	return NULL;
}
BST::Node* BST::Search(int key) {
	return BST::Search_private(root, key);
}
int  BST::Minimum_private(Node* ptr) {
	if (ptr == NULL) {
		cout << "The tree is empty.\n";
		return -1000;
	}
	else {
		if (ptr->left != NULL)
			Minimum_private(ptr->left);
		else return ptr->val;
	}
	return NULL;
}
int BST::Minimum() {
	return BST::Minimum_private(root);
}
void BST::RemoveNodePrivate(Node* parent,int key) {
	if (parent != NULL) {
		if (parent->val == key)
			RemoveRootMatch();
		else {
			if (key < parent->val&&parent->left != NULL)
				parent->left->val == key ? RemoveNodeMatch(parent, parent->left, true) :
				RemoveNodePrivate(parent->left, key);
			else if (key > parent->val&&parent->right != NULL)
				parent->right->val == key ? RemoveNodeMatch(parent, parent->right, false) :
				RemoveNodePrivate(parent->right, key);
			else
				cout << "The key" << key << "was not found in the tree.\n";
		}
			
	}
	else
		cout << "The tree is empty.\n";
}
void BST::RemoveNode(int key) {
	BST::RemoveNodePrivate(root, key);
}
void BST::RemoveRootMatch() {
	if (root != NULL) {
		Node* delptr = root;
		int rootKey = root->val;
		int smallestInRightSubtree;
		if (root->left == NULL&&root->right == NULL) {
			root = NULL;
		}
		else if (root->left == NULL&&root->right != NULL) {
			root = root->right;
			delptr->right = NULL;
			cout << "The root nod with key " << rootKey << "was deleted." <<
				"The new root contains key " << root->val << endl;
		}
		else if (root->left != NULL&&root->right == NULL) {
			root = root->left;
			delptr->left = NULL;

			cout << "The root node with key " << rootKey << "was deleted." <<
				"The new root contains key " << root->val << endl;
		}
		else {
			smallestInRightSubtree = Minimum_private(root->right);
			RemoveNodePrivate(root, smallestInRightSubtree);
			root->val = smallestInRightSubtree;
			cout << "The root key contains key " << rootKey << "was overwritten with key " << root->val << endl;
		}
		delete delptr;
		delptr = NULL;
	}
	else
		cout << "Can not remove the root.The tree is empty.\n";
}
void BST::RemoveNodeMatch(Node* parent, Node* match, bool left) {
	if (root != NULL) {
		Node* delptr=NULL;
		int matchkey = match->val;
		int smallestInRightSubtree;
		if (match->left == NULL&&match->right == NULL) {
			delptr = match;
			left == true ? parent->left == NULL : parent->right == NULL;
			cout << "The node containing key " << matchkey << "was removed.\n";
		}
		else if (match->left == NULL&&match->right != NULL) {
			left == true ? parent->left = match->right : parent->right = match->right;
			match->right = NULL;
			cout << "The node containing key " << matchkey << "was removed.\n";
		}
		else if (match->left != NULL&&match->right == NULL) {
			left == true ? parent->left = match->left : parent->right = match->left;
			match->left = NULL;
			delptr = match;
			cout << "The node containing key " << matchkey << "was removed.\n";
		}
		else {
			smallestInRightSubtree = Minimum_private(match->right);
			RemoveNodePrivate(match, smallestInRightSubtree);
			match->val = smallestInRightSubtree;
		}
		delete delptr;
		delptr = NULL;
	}
	else
		cout << "Can not remove match.The tree is empty.\n ";
}
