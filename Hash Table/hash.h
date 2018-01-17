#pragma once
#include "stdafx.h"
#include<iostream>
#include<string>

using std::string;

#ifndef HASH_H
#define HASH_H
#endif // !HASH_H

class hash {
private:
	static const int tableSize=40;

	struct item {
		string name;
		string drink;
		item* next;
	};
	item* HashTable[tableSize];
public:
	hash();
	int Hash(string key);
	void AddItem(string name, string drink);
	int NumberOfItemsInIndex(int index);
	void PrintTable();
	void PrintItermInIndex(int index);
	void FindDrink(string name);
	void RemoveItem(string name);
};
