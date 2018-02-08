#ifndef BST_H
#define BST_H
#endif // !BST.H


class BST {
private:
	struct Node {
		int val;
		Node* left;
		Node* right;
	};
	Node* root;

	void Insert_private(Node* ptr, int key);
	void PrintInOrder_private(Node* ptr);
	Node* Search_private(Node* ptr, int key);
	int Minimum_private(Node* ptr);
	void RemoveNodePrivate(Node* parent, int key);
	void RemoveRootMatch();
	void RemoveNodeMatch(Node* parent,Node* match,bool left);
	Node* CreateLeaf(int key);
public:
	BST();
	
	void Insert(int key);
	void PrintInOrder();
	Node* Search(int key);
	int Minimum();
	void RemoveNode(int key);
};