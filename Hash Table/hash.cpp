#include "stdafx.h"
#include<iostream>
#include<string>

#include "hash.h"
using std::string;
hash::hash() {
	for (int i = 0; i < tableSize; ++i) {
		HashTable[i] = new item;
		HashTable[i]->name = "empty";
		HashTable[i]->drink = "empty";
		HashTable[i]->next = NULL;			
	}
}
void hash::AddItem(string name, string drink) {
	int index = Hash(name);
	if (HashTable[index]->name == "empty") {
		HashTable[index]->name = name;
		HashTable[index]->drink = drink;
		HashTable[index]->next = NULL;
	}
	else{
		item* Ptr = HashTable[index];
		item* n = new item;
		n->name = name;
		n->drink = drink;
		n->next = NULL;
		while (Ptr->next != NULL)
			Ptr = Ptr->next;
		Ptr->next = n;
	}

}
int hash::NumberOfItemsInIndex(int index) {
	int count = 0;
	if (HashTable[index]->name == "empty") 
		return count;
	else {
		++count;
		item* Ptr = HashTable[index];
		while (Ptr->next != NULL) {
			++count;
			Ptr = Ptr->next;
		}
	}
	return count;
}
void hash::PrintTable() {
	int number;
	for (int i = 0; i < tableSize; ++i) {
		number = NumberOfItemsInIndex(i);
		std::cout << "--------------\n";
		std::cout << "index=" << i << std::endl;
		std::cout << HashTable[i]->name << std::endl;
		std::cout << HashTable[i]->drink << std::endl;
		std::cout << "# of items=" << number << std::endl;
		std::cout << "--------------\n";
	}
}
void hash::PrintItermInIndex(int index) {
	item* Ptr = HashTable[index];
	if (Ptr->name == "empty") {
		std::cout << "index=" << index << "is empty" << std::endl;
	}
	else {
		std::cout << "index " << index << " contains the following item\n";
		while (Ptr!=NULL) {
			std::cout << "--------------\n";
			std::cout << Ptr->name << std::endl;
			std::cout << Ptr->drink << std::endl;
			std::cout << "--------------\n";
			Ptr = Ptr->next;
		}
	}

}

int hash::Hash(string key) {
	int hash = 0;
	int index;
	
	for (int i = 0; i < key.length(); ++i) {
		hash = (hash + (int)key[i])*17;
	}
	index = hash%tableSize;
	return index;
}
void hash::FindDrink(string name) {
	string drink;
	int index = Hash(name);
	bool foundName = false;
	item* Ptr = HashTable[index];
	while (Ptr!=NULL) {
		if (Ptr->name == name) {
			foundName = true;
			drink = Ptr->drink;
		}
		Ptr = Ptr->next;
	}
	if (foundName == true)
		std::cout << "Favorite drink= " << drink << std::endl;
	else
		std::cout << name << "'s info was not found in the Hash Table\n";
}
void hash::RemoveItem(string name) {
	int index = Hash(name);
	item* delPtr;
	item *P1, *P2;
	if (HashTable[index]->name == "empty"&&HashTable[index]->drink == "empty")
		std::cout << name << " was not found in the Hash Table/n";
	else if (HashTable[index]->name == name&&HashTable[index]->next == NULL) {
		HashTable[index]->name = "empty";
		HashTable[index]->drink = "empty";
		std::cout << name << " was deleted from the Hash Table\n";
	}
	else if (HashTable[index]->name == name) {
		delPtr = HashTable[index];
		HashTable[index] = HashTable[index]->next;
		delete delPtr;
		std::cout << name << " was deleted from the Hash Table\n";
	}
	else {
		P1 = HashTable[index]->next;
		P2 = HashTable[index];
		while (P1 == NULL&&P1->name == name) {
			P2 = P1;
			P1 = P1->next;
		}
		if(P1==NULL)
			std::cout << name << " was not found in the Hash Table\n";
		else {
			delPtr = P1;
			P1 = P1->next;
			P2->next = P1;
			delete delPtr;
			std::cout << name << " was deleted from the Hash Table\n";
		}

	}

}