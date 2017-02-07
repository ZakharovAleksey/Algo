#pragma once

#ifndef BIN_TREE_IMPL
#define BIN_TREE_IMPL

#include<iostream>

#include"bin_tree.h"

template<typename T>
BinaryTree<T>::BinaryTree() : root_(nullptr) { }


template<typename T>
BinaryTree<T>::~BinaryTree() {}

template<typename T>
inline void BinaryTree<T>::Add(T const & value)
{
	// If tree is empty create the root
	if (!root_)
	{
		root_ = std::make_unique<Node<T>>(value);
	}
	else
	{
		Node<T>* curNode = root_.get();
		Node<T>* parent;

		// Loop until we find appropriate place for insert
		while (curNode)
		{
			parent = curNode;

			if (value <= curNode->value)
				curNode = curNode->left.get();
			else
				curNode = curNode->right.get();
		}

		// Insert a new node with 'value' argument
		if (value <= parent->value)
			parent->left = std::make_unique<Node<T>>(value);
		else
			parent->right = std::make_unique<Node<T>>(value);

	}
}

template<typename T>
inline bool BinaryTree<T>::IsBalanced()
{
	// Height of the tree
	long int height{ 0 };
	return IsBalanced(root_, &height);
}

template<typename T>
inline void BinaryTree<T>::RandomFill(long int const & treeSize, long int const & min = 0, long int const & max = 100)
{
	for (int i = 0; i < treeSize; ++i)
		Add(min + rand() % (max - min));
}

template<typename T>
inline void BinaryTree<T>::PreOrder(const NodePtr & root) const
{
	if (root == nullptr)
		return;
	std::cout << root->value << " ";
	PreOrder(root->left);
	PreOrder(root->right);

}

template<typename T>
inline bool BinaryTree<T>::IsBalanced(const NodePtr & root, long int* const curHeight)
{
	if (!root)
	{
		*curHeight = 0;
		return true;
	}

	// Height of left(right) sub-tree of current node
	long int leftHeight{ 0 };
	long int rightHeight{ 0 };

	// true if left(right) sub-tree is balanced
	bool isLeftBalanced = false;
	bool isRightBalanced = false;

	isLeftBalanced = IsBalanced(root->left, &leftHeight);
	isRightBalanced = IsBalanced(root->right, &rightHeight);

	*curHeight = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;

	return (std::abs(leftHeight - rightHeight) > 1) ? false : (isLeftBalanced && isRightBalanced);
}


template<typename T>
inline void BinaryTree<T>::Print() const
{
	PreOrder(root_);
	std::cout << std::endl;
}



#endif // !BIN_TREE_IMPL
