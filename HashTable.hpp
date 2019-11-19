#include "LinkedList.hpp"

template <typename K>
class Hasher
{
public:
	virtual unsigned int hashCode(K key) = 0;
};

template <typename K>
class EqualityPredicate
{
public:
	virtual bool isEqual(K left, K right) = 0;
};

template <typename K, typename V>
class HashNode
{
public:
	K key;
	V value;

	HashNode() {}
	HashNode(K key, V value)
	{
		this->value = value;
		this->key = key;
	}
};

template <typename K, typename V>
class HashTable
{
private:
	int capacity;
	//hash element array 
	LinkedList<HashNode<K,V> > **arr;
	Hasher<K>* hasher;
	EqualityPredicate<K>* equalityPredicate;

public:
	HashTable(int capacity, Hasher<K>* hasher, EqualityPredicate<K>* equalityPredicate)
	{
		this->capacity = capacity;
		this->hasher = hasher;
		this->equalityPredicate = equalityPredicate;

		arr = new LinkedList<HashNode<K, V> >*[capacity];

		//Initialise all elements of array as NULL 
		for (int i = 0; i < capacity; i++)
			arr[i] = NULL;
	}

	~HashTable() 
	{
		if (NULL != arr)
			for(int i=0; i<capacity; i++)
				delete arr[i];
	}

	void insert(K key, V value)
	{
		HashNode<K, V>* temp = new HashNode<K, V>(key, value);
		int v = this->hasher->hashCode(key);
		int index = v % capacity;

		LinkedList< HashNode<K, V> >* linkedList = arr[index];
		if (linkedList == NULL)
		{
			linkedList = new LinkedList<HashNode<K, V> >();
			arr[index] = linkedList;
		}

		// check if key is duplicate
		ListIterator<HashNode<K, V> > iterator = linkedList->Iterator();
		while (iterator.HasNext())
		{
			HashNode<K, V> n = *iterator;
			if (this->equalityPredicate->isEqual(n.key, key))
				throw "Duplicate key";

			iterator++;
		}

		// add to linked list
		linkedList->Add(*temp);
	}

	V get(K key)
	{
		int index = this->hasher->hashCode(key) % capacity;
		LinkedList<HashNode<K, V> >* linkedList = arr[index];
		if (linkedList == NULL)
			return NULL;

		ListIterator<HashNode<K, V> > iterator = linkedList->Iterator();
		while (iterator.HasNext())
		{
			HashNode<K, V> n = *iterator;
			if (this->equalityPredicate->isEqual(n.key, key))
				return n.value;

			iterator++;
		}
		//If not found return null 
		return NULL;
	}
};