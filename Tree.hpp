#include <iostream>

template <typename T>
class BSTNode
{
public:
	T key;
	BSTNode* left;
	BSTNode* right;
	BSTNode* parent;
};

template <typename T>
class BST
{
public:
	BST() { this->root = NULL; }

	void insert(T key) 
	{
		BSTNode<T>* node = this->insert(this->root, key);
		if (this->root == NULL)
			this->root = node;
	}

	void printTree() 
	{ 
		this->printTree(this->root); 
		std::cout << std::endl;
	}

	bool search(T key) { return search(this->root, key); }

private:
	BSTNode<T>* root;

	BSTNode<T>* insert(BSTNode<T>* node, T key)
	{
		if (NULL == node)
		{
			node = new BSTNode<T>();
			node->key = key;
			node->left = NULL;
			node->right = NULL;
			node->parent = NULL;
		}
		else if (root->key < key)
		{
			node->right = insert(node->right, key);
			node->right->parent = node;
		}
		else
		{
			node->left = insert(node->left, key);
			node->left->parent = node;
		}

		return node;
	}

	void printTree(BSTNode<T>* node)
	{
		if (node == NULL) return;

		this->printTree(node->left);
		std::cout << node->key << ",";

		this->printTree(node->right);
	}

	bool search(BSTNode<T>* node, T key)
	{
		if (NULL == node) return NULL;
		else if (node->key == key) return node;
		else if (key > node->key) return search(node->right, key);
		else return search(node->left, key);
	}
};
