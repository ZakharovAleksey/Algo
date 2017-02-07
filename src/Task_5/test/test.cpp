#include"test.h"

#include<cstdlib>

Task5Test::Task5Test(long int testCount) : testCount_(testCount) {}

Task5Test::~Task5Test() {}

void Task5Test::TestFunction(long int const & treeSize) const
{
	for (int i = 0; i < testCount_; ++i)
	{
		BinaryTree<int> binTree;
		binTree.RandomFill(treeSize);

		// Print a message according to IsBalanced() return value
		if (binTree.IsBalanced())
			std::cout << "Balanced binary tree: ";
		else
			std::cout << "Not balanced binary tree: ";

		binTree.Print();
	}
	

	
}
