#pragma once

#include <cstddef>
#include <iostream>

template <typename T>
class Node
{
public:
	Node(T data)
	{
		this->data = data;
		this->next = NULL;
	}
	virtual ~Node() 
	{
		if (NULL != next)
			delete next;
	};

	void setNext(Node<T>* next) { this->next = next; }
	Node<T>* getNext() { return this->next; }
	T getData() { return this->data; }

private:
	T data;
	Node* next;
};

template <typename T>
class ListIterator
{
public:
	ListIterator(Node<T>* node) { this->currNode = node; }
	~ListIterator() { }

	bool HasNext() {return NULL != currNode; }
	T operator*() const { return currNode->getData(); }
	ListIterator<T> operator++(int) { currNode = currNode->getNext(); return *this; }

private:
	Node<T>* currNode;
};

template <typename T>
class LinkedList
{
public:
	LinkedList()
	{
		this->size = 0;
		this->head = this->tail = NULL;
	}

	~LinkedList()
	{
		if (NULL != head)
			delete head;
	}

	void Add(T& value)
	{
		Node<T>* node = new Node<T>(value);
		// if empty list
		if (NULL == this->head)
			this->head = node;
		else
			this->tail->setNext(node);

		this->tail = node;
		this->size++;
	}

	void Insert(T& value, int index)
	{
		if (index > this->Size() || index < 0)
			throw "index is outside of linked list size";

		// create node
		Node<T>* t = new Node<T>(value);

		int temp_index = 0;
		Node<T>* index_node = this->head;
		Node<T>* previous_node = NULL;
		while (temp_index < index)
		{
			previous_node = index_node;
			index_node = index_node->getNext();
			temp_index++;
		};

		if (previous_node == NULL)
			this->head = t;
		else
			previous_node->setNext(t);

		t->setNext(index_node);

		if (index_node == this->tail)
			this->tail = t;

		this->size++;
	}

	T& Get(int index)
	{
		int temp_index = 0;
		Node<T>* temp_node = this->head();
		while (temp_index <= index)
		{
			temp_node = temp_node->getNext();
			temp_index++;
		}

		return temp_node->getData();
	}

	int IndexOf(T& value)
	{
		int temp_index = 0;
		Node<T>* temp_node = this->head();
		while (temp_index < this->size())
		{
			if (temp_node->getData() == value)
				return temp_index;

			temp_node = temp_node->getNext();
			temp_index++;
		}

		return -1; // not found. can throw exception
	}

	void Remove(int index)
	{
		if (index >= this->Size() || index < 0)
			throw "index is outside of linked list size";

		int temp_index = 0;
		Node<T>* index_node = this->head;
		Node<T>* previous_node = NULL;
		while (temp_index < index)
		{
			previous_node = index_node;
			index_node = index_node->getNext();
			temp_index++;
		};

		if (previous_node == NULL)
			this->head = index_node->getNext();
		else
			previous_node->setNext(index_node->getNext());

		if (index_node->getNext() == NULL)
			this->tail = previous_node;

		delete index_node;
		this->size--;
	}

	ListIterator<T> Iterator(){return ListIterator<T>(this->head);}
	int Size() { return this->size;	}
	Node<T>* getHead() { return head; }
	Node<T>* getTail() { return tail; }

	void print()
	{
		Node<T>* curr = this->head;
		while (curr != NULL)
		{
			std::cout << curr->getData() << " ";
			curr = curr->getNext();
		}
		std::cout << std::endl;
	}

protected:
	Node<T>* head;
	Node<T>* tail;
	int size;
};

