#pragma once

#ifndef TEST
#define TEST

#include"../bin_tree/bin_tree.h"

class Task5Test
{
public:
	Task5Test(long int testCount);
	~Task5Test();

	/// <summary>
	/// Generates trees and then checks whether those trees are balanced.
	/// </summary>
	/// <param name="treeSize"> Size of generated trees. </param>
	void TestFunction(long int const & treeSize)const;

private:
	// Number of tests for execution
	long int testCount_;
};

#endif // !TEST
