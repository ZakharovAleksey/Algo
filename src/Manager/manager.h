#pragma once

#ifndef MANAGER_H
#define MANAGER_H

#include"../Task_5/test/test.h";

#include"../Task_6/Generator/generator.h"
#include"../Task_6/Graph/graph.h"


class Manager
{
public:
	Manager();
	~Manager();

	void TaskLoop();

private:
	void ChooseTaskNumber();


	void ExecutionTask5() const;
	void InputValue(int & value, const std::string & errorMessage) const;


	void ExecutionTask6() const;

	int curTaskNumber;
};

#endif // !MANAGER_H
