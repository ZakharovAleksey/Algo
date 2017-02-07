#pragma once

#ifndef BIN_TREE
#define BIN_TREE

#include<memory>

// Binary Tree implementation
template<typename T>
class BinaryTree
{
public:
	BinaryTree();
	~BinaryTree();

	/// <summary>
	/// Adds a new element at the binary tree. The content of 'value' copied moved to the new element.
	/// </summary>
	/// <param name="value"> Value to be copied to the new element. </param>
	void Add(T const & value);

	/// <summary>
	/// Returns whether the binary tree is balanced.
	///		<remarks>
	///		The binary tree is balanced if for each node the heights of its left and right sub-trees differ by at most 1.
	///		</remarks>
	/// </summary>
	/// <returns> True if the binary tree is balanced, false otherwise. </returns>
	bool IsBalanced();

	/// <summary>
	/// Provide generation of a tree at random. Fills tree with 'treeSize' random elements in ['min','max'] range.
	/// </summary>
	/// <param name="treeSize"> Number of elements, added to the binary tree.</param>
	/// <param name="min"> Minimum possible random value. </param>
	/// <param name="max"> Maximum possible random value. </param>
	void RandomFill(long int const & treeSize, long int const & min = 0, long int const & max = 100);

	/// <summary>
	/// Display the binary tree in pre_order type.
	/// </summary>
	void Print() const;

private:

	template<typename T1>
	struct Node;

	typedef std::unique_ptr<Node<T>> NodePtr;

	// The Node of binary tree.
	template<typename T1>
	struct Node
	{
		T1 value;

		NodePtr left;
		NodePtr right;

		Node(T1 value) : value(value), left(nullptr), right(nullptr) {}

	};
	
	// Binary tree pre order traversal
	void PreOrder(const NodePtr & root) const;
	// Returns whether the binary tree with root is in 'root' is balanced
	bool IsBalanced(const NodePtr & root, long int* const height);


	std::unique_ptr<Node<T>> root_;
};

#include"bin_tree_impl.h"

#endif // !BIN_TREE
