#pragma once

#include <iostream>
#include <cstddef>
#include "LinkedList.hpp"

template <typename T>
class DNode : public Node<T>
{
public:
	DNode(T data) : Node<T>::Node(data)
	{
		this->previous = NULL;
	}

	~DNode() {};

	void setPrevious(Node<T>* previous) { this->previous = previous; }
	Node<T>* getPrevious() { return this->previous; }
	
private:
	Node<T>* previous;
};

template <typename T>
class DoublyLinkedList : public LinkedList<T>
{
public:
	void Add(T& value)
	{
		DNode<T>* node = new DNode<T>(value);
		// if empty list
		if (NULL == this->head)
			this->head = node;
		else
		{
			this->tail->setNext(node);
			node->setPrevious(this->tail);
		}
		
		this->tail = node;
		this->size++;
	}

	void Insert(T& value, int index)
	{
		if (index > this->Size() || index < 0)
			throw "index is outside of linked list size";

		// create node
		DNode<T>* t = new DNode<T>(value);

		int temp_index = 0;
		DNode<T>* index_node = dynamic_cast<DNode<T> *>(this->head);
		DNode<T>* previous_node = NULL;
		while (temp_index < index)
		{
			previous_node = index_node;
			index_node = dynamic_cast<DNode<T> *>(index_node->getNext());
			temp_index++;
		};

		if (previous_node == NULL)
			this->head = t;
		else
		{
			previous_node->setNext(t);
			t->setPrevious(previous_node);
		}

		t->setNext(index_node);
		index_node->setPrevious(t);

		if (index_node == this->tail)
			this->tail = t;

		this->size++;
	}

	void Remove(int index)
	{
		if (index >= this->Size() || index < 0)
			throw "index is outside of linked list size";

		int temp_index = 0;
		DNode<T>* index_node = dynamic_cast<DNode<T> *>(this->head);
		DNode<T>* previous_node = NULL;
		while (temp_index < index)
		{
			previous_node = index_node;
			index_node = dynamic_cast<DNode<T> *>(index_node->getNext());
			temp_index++;
		};

		if (previous_node == NULL)
			this->head = index_node->getNext();
		else
		{
			DNode<T>* next_node = dynamic_cast<DNode<T> *>(index_node->getNext());
			previous_node->setNext(next_node);
			next_node->setPrevious(previous_node);
		}

		if (index_node->getNext() == NULL)
			this->tail = previous_node;

		delete index_node;
		this->size--;
	}
};