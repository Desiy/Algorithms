// RBTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RBT.h"

using namespace std;

int main()
{
	RBT mytree = RBT::RBT();
	mytree.addNode(1);
	mytree.addNode(2);
	mytree.addNode(4);
	mytree.addNode(5);
	mytree.addNode(7);
	mytree.addNode(8);
	mytree.addNode(11);
	mytree.addNode(14);
	mytree.addNode(15);
	mytree.printInOrder();
    return 0;
}

