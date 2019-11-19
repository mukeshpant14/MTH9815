#pragma once

#include "DLinkedList.hpp"
#include "HashTable.hpp"
#include <string>
#include <cmath>
#include <functional>
#include <iomanip>

void testLinkedList()
{
	LinkedList<int>* list = new LinkedList<int>();
	std::cout << "--------- Singly Linked List ------------" << std::endl;
	std::cout << "Test Add:" << std::endl;
	for (int i = 0; i < 5; i++)
	{
		int value = i * 2;
		list->Add(value);
	}

	list->print();

	std::cout << "Test Insert:" << std::endl;
	int v1 = 1000;
	list->Insert(v1, 0);
	list->Insert(v1, 3);

	list->print();

	std::cout << "Test Remove:" << std::endl;
	list->Remove(5);
	list->print();

	std::cout << "Test Iterator:" << std::endl;
	for (ListIterator<int> iterator = list->Iterator(); iterator.HasNext(); iterator++)
		std::cout << *iterator << std::endl;

	std::cout << std::endl;
}

void testDoublyLinkedList()
{
	DoublyLinkedList<int>* list = new DoublyLinkedList<int>();
	std::cout << "--------- Doubly Linked List ------------" << std::endl;
	std::cout << "Test Add:" << std::endl;
	for (int i = 0; i < 10; i++)
	{
		int value = i * 3;
		list->Add(value);
	}

	list->print();

	std::cout << "Test Insert:" << std::endl;
	int v1 = 1000;
	list->Insert(v1, 0);
	list->Insert(v1, 3);

	list->print();

	std::cout << "Test Remove:" << std::endl;
	list->Remove(5);
	list->print();

	std::cout << "Test Iterator:" << std::endl;
	for (ListIterator<int> iterator = list->Iterator(); iterator.HasNext(); iterator++)
		std::cout << *iterator << std::endl;

	std::cout << std::endl;
}

class IntHasher : public Hasher<int>
{
public:
	unsigned int hashCode(int key) 
	{
		return key;
		// std::hash is not compile in g++
		//std::hash<int> h;
		//return std::abs(static_cast<int>(h(key)));
	}
};

class IntEqualityPredicate : public EqualityPredicate<int>
{
public:
	bool isEqual(int left, int right)
	{
		return left == right;
	}
};

void testHashTable()
{
	std::cout << "----------------- Hash Table ---------------" << std::endl;
	Hasher<int>* hasher = new IntHasher();
	EqualityPredicate<int>* equalityPredicate = new IntEqualityPredicate();

	HashTable<int, std::string>* table = new HashTable<int, std::string>(20, hasher, equalityPredicate);
	table->insert(1, "ABC");
	table->insert(21, "PQR");
	table->insert(41, "XYZ");
	table->insert(2, "DEF");
	table->insert(22, "DEF");

	std::cout << "key: 1, value: " << table->get(1) << std::endl;
	std::cout << "key: 21, value: " << table->get(21) << std::endl;
	std::cout << "key: 41, value: " << table->get(41) << std::endl;
	std::cout << "key: 2, value: " << table->get(2) << std::endl;
	std::cout << "key: 22, value: " << table->get(22) << std::endl;

	delete table;
	delete hasher;
	delete equalityPredicate;
}

int main() 
{
	testLinkedList();
	testDoublyLinkedList();
	testHashTable();

	//std::cout << std::hash<int>{}(1) % 20 << std::endl;

	std::cout << "\n----------- Press Any key to quit! -------------\n" << std::endl;
	std::cin.get();

	return 0;
}
