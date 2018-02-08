#include <string>

using namespace std;
class RBT {
private:
	enum  Color
	{
		RED, BLACK,
	};
	struct node {
		int key;
		node* left;
		node* right;
		node* parent;
		Color color;
	};
	node* root;
	void addNode_private(node* ptr, int key);
	void addNode_fixup(node* ptr);
	void leftRotate(node* ptr);
	void rightRotate(node* ptr);
	void printInOrder_private(node* ptr);
	void remove_private(node* ptr, int key);
	void transplant( node* u, node* v);
	node* minimum_private(node* ptr);
	void removefixup(node* ptrpn, node* ptr);
public:
	RBT();
	node* creatLeaf(int key);
	void addNode(int key);
	void printInOrder();
	void remove(int key);
	node* minimum();


};