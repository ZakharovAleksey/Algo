#pragma once

#ifndef MANAGER_H
#define MANAGER_H

#include"../Task_5/test/test.h";

#include"../Task_6/Generator/generator.h"
#include"../Task_6/Graph/graph.h"

#include <functional>


/// <summary>
/// Manger class implementation.
/// Performs interface for the user - computer intearaction,
/// and performs Task 5 or Task 6 execution depending on the user input.
/// </summary>
class Manager
{
public:
	Manager();
	~Manager();

	/// <summary>
	/// Performs interface for the user-computer intearaction.
	/// </summary>
	void TaskLoop();

private:

	// Number performed at a given time task
	int curTaskNumber;

	/// <summary>
	/// Helps user to choose number of task correctly.
	/// </summary>
	void ChooseTaskNumber();
	/// <summary>
	/// This function try to read user input in 'value' variable. 
	/// If the variable 'value' is successfully read and it's value satisfy 'condPtr' - stops execution, display error message otherwise.
	/// </summary>
	/// <param name="value"> The variable in which the user enters a value. </param>
	/// <param name="errorMessage"> Error message, which is displaying on screen if user is enter not appropriate value. </param>
	/// <param name="condPtr"> A pointer to a function, which must return true for input 'value'. </param>
	void InputValue(int & value, const std::string & errorMessage, std::function<bool(int)> condPtr) const;

	/// <summary>
	/// Starts Task 5 execution: Checking whether a tree is balanced.
	/// </summary>
	void ExecutionTask5() const;
	/// <summary>
	/// Starts Task 5 execution: Armata's width determination.
	/// </summary>
	void ExecutionTask6() const;

	/// <summary>
	/// Execute a response to user input in format 'opt.exe -g number_of_cities number_of_roads output_file_name' command in Task 6
	/// </summary>
	/// <param name="lineParts"> User input string, which splitted by 'space' key.  </param>
	void ExecuteGraphGeneration(const std::vector<std::string> & lineParts) const;
	/// <summary>
	/// Execute a response to user input in format 'opt.exe -t input_file_name' command in Task 6
	/// </summary>
	/// <param name="lineParts">  User input string, which splitted by 'space' key. </param>
	void ExecuteGraphTest(const std::vector<std::string> & lineParts) const;
};

#endif // !MANAGER_H
