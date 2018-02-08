#include <string>;

#include "RBT.h"
#include <iostream>


using namespace std;

RBT::RBT() {
	root = NULL;
}

RBT::node* RBT::creatLeaf(int key) {
	node* n = new node;
	n->key = key;
	n->left = NULL;
	n->right = NULL;
	n->parent = NULL;
	n->color = RED;
	return n;
}
void RBT::leftRotate(node* ptr) {
	if (ptr->right != NULL) {
		node* y = ptr->right;
		if (y->left != NULL) {
			ptr->right = y->left;
			y->left->parent = ptr;
		}
		else
			ptr->right = NULL;
		if (ptr->parent != NULL)
			y->parent = ptr->parent;
		if (ptr->parent == NULL) {
			root = y;
			y->left = ptr;
			root->parent = NULL;
		}
		else if (ptr == ptr->parent->left)
			ptr->parent->left = y;
		else ptr->parent->right = y;
		y->left = ptr;
		ptr->parent = y;
	}
}
void RBT::rightRotate(node* ptr) {
	if (ptr->left != NULL) {
		node* y = ptr->left;
		if (y->right != NULL) {
			ptr->left = y->right;
			y->right->parent = ptr;
		}
		else
			ptr->left = NULL;
		if (ptr->parent != NULL)
			y->parent = ptr->parent;
		if (ptr->parent == NULL) {
			root = y;
			y->right = ptr;
			root->parent = NULL;
		}
		if (ptr->parent!=NULL&&ptr == ptr->parent->right)
			ptr->parent->right = y;
		else if(ptr->parent!=NULL) ptr->parent->left = y;
		y->right = ptr;
		ptr->parent = y;
	}
}
void RBT::addNode_fixup(node* ptr) {
	while (ptr->parent!=NULL&&ptr->parent->color == RED) {
		if (ptr->parent->parent != NULL) {
			node* p = ptr->parent->parent;
			if (p->left == ptr->parent) {
				if (p->right != NULL) {
					node* rt = p->right;
					if (rt->color==RED) {
						ptr->parent->color = BLACK;
						rt->color = BLACK;
						ptr->parent->parent->color = RED;
						ptr = ptr->parent->parent;
					}
					else if (ptr == ptr->parent->right) {
						ptr = ptr->parent;
						leftRotate(ptr);
					}
					else {
						ptr->parent->color = BLACK;
						ptr->parent->parent->color = RED;
						ptr = p;
						rightRotate(ptr);
					}
				}
				else {
					ptr->parent->color = BLACK;
					ptr->parent->parent->color = RED;
					ptr = p;
					rightRotate(ptr);
				}
			}
			else {
				if (p->left != NULL) {
					node* lt = p->left;
					if (lt->color == RED) {
						ptr->parent->color = BLACK;
						lt->color = BLACK;
						ptr->parent->parent->color = RED;
						ptr = ptr->parent->parent;
					}
					else if (ptr == ptr->parent->left) {
						ptr = ptr->parent;
						rightRotate(ptr);
					}
					else {
						ptr->parent->color = BLACK;
						ptr->parent->parent->color = RED;
						ptr = p;
						leftRotate(ptr);
					}
				}
				else {
					ptr->parent->color = BLACK;
					ptr->parent->parent->color = RED;
					ptr = p;
					leftRotate(ptr);
				}
			}
		}
	}
	root->color = BLACK;
}


void RBT::addNode_private(node* ptr, int key) {
	while (ptr != NULL) {
		if (key < ptr->key) {
			if (ptr->left != NULL)
				ptr = ptr->left;
			else break;
		}
		else if (key > ptr->key) {
			if (ptr->right != NULL)
				ptr = ptr->right;
			else break;
		}
	}
	node* n = creatLeaf(key);
	n->parent = ptr;
	if (ptr == NULL) root = n;
	else if (key < ptr->key) ptr->left = n;
	else ptr->right = n;
	addNode_fixup(n);
}

void RBT::addNode(int key) {
	RBT::addNode_private(root, key);
}
void RBT::printInOrder_private(node* ptr) {
	if (ptr != NULL) {
		if (ptr->left != NULL)
			printInOrder_private(ptr->left);
		cout << "key=" << ptr->key << endl;
		cout << "color=" << ptr->color << endl;
	     if (ptr->right != NULL)
			printInOrder_private(ptr->right);
	}
}
void RBT::printInOrder() {
	printInOrder_private(root);
}

RBT::node*  RBT::minimum_private(node* ptr) {
	if (ptr == NULL) {
		cout << "The tree is empty.\n";
		return NULL;
	}
	else {
		if (ptr->left != NULL)
			minimum_private(ptr->left);
		else return ptr;
	}
}
RBT::node* RBT::minimum() {
	return minimum_private(root);
}
void RBT::transplant( node* u, node* v) {
	if (u->parent == NULL) {
		root = v;
		root->parent = NULL;
	}
	else if (u == u->parent->left)
		u->parent->left = v;
	else u->parent->right = v;
	if(v!=NULL) v->parent = u->parent;
}
void RBT::removefixup(node* ptrpn,node* ptr) {
	if (ptrpn != NULL) {
		node* w = NULL;
		bool inLeftTree = true;
		if (ptr == ptrpn->left)
			w = ptrpn->right;
		else {
			w = ptrpn->left;
			inLeftTree = false;
		}
		if (w!=NULL&&w->color == RED) {
			w->color = RED;
			ptrpn->color = RED;
			if (inLeftTree)
				leftRotate(ptrpn);
			else
				rightRotate(ptrpn);
			removefixup(ptr, ptrpn);
		}
		else {
			if ((w->left==NULL&&w->right==NULL)||w->left->color == BLACK&&w->right->color == BLACK) {
				w->color = RED;
				ptr = ptrpn;
				if (ptr->color == RED)
					ptr->color = BLACK;
				else
					removefixup(ptr->parent, ptr);
			}
			else if((inLeftTree&&w->right!=NULL&&w->right->color== RED)
				||(!inLeftTree&&w->left!=NULL&&w->left->color== RED)){
				bool isRed = (ptrpn->color == RED);
				ptrpn->color = w->color;
				w->color = (isRed == true ? RED : BLACK);

				if (inLeftTree) {
					w->right->color = BLACK;
					leftRotate(ptrpn);
				}
				else {
					w->left->color = BLACK;
					rightRotate(ptrpn);
				}
			}
			else {
				w -> color = RED;
				if (inLeftTree) {
					w->left->color = BLACK;
					rightRotate(w);
					removefixup(ptrpn, ptr);
				}
				else {
					w->right->color = BLACK;
					leftRotate(w);
					removefixup(ptrpn, ptr);
				}
			}
		}
	}
	root->color = BLACK;
}

void RBT::remove_private(node* ptr,int key) {
	bool found = false;
	node* y = ptr, *x = NULL, *xpn = NULL;
	while (y!=NULL&&found == false) {
		if (key == y->key) {
			ptr = y;
			found = true;
		}
		else if (key < y->key)
			y = y->left;
		else y=y->right;
	}
	if (y == NULL) {
		cout << "Can not find the key in RB-Tree." << endl;
		return;
	}
	Color color_original = y->color;
	if (y->left==NULL) {
		x = y->right;
		xpn = y->parent;
		transplant(y, y->right);
	}
	else if (y->right == NULL) {
		x = y->left;
		xpn = y->parent;
		transplant(y, y->left);
	}
	else {
		y = minimum_private(ptr->right);
		x = y->right;
		if (y->parent == ptr) {
			if(x!=NULL)
				x->parent = y;
			xpn = y;
		}
		else {
			transplant(y, y->right);
			y->right = ptr->right;
			y->right->parent = y;
		}
		transplant(ptr, y);

		y->left = ptr->left;
		if(y->left!=NULL)
			y->left->parent = y;
		y->color = ptr->color;
		xpn = x->parent;

	}
	if (color_original == BLACK)
		removefixup(xpn,x);
}
void RBT::remove(int key) {
	remove_private(root, key);
}
