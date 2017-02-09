#include"manager.h"

#include <iterator>
#include <sstream>

// Checks whether the value of 'value' variable is in the range
bool IsInRange(const int & value)
{
	return (value < 0 || value > int(1e6));
}

// Checks whether the value of 'value' takes one of above values
bool IsCorrectTaskNumber(const int & value)
{
	return (value != 5 && value != 6 && value != -1);
}



Manager::Manager() {}

Manager::~Manager() {}

void Manager::TaskLoop()
{
	std::cout << "WELCOME TO HUAWEI TASK SOLVER!\n\n" <<
		"Input number of choosen task:\n" <<
		"  5 - Checking whether a tree is balanced.\n" <<
		"  6 - Armata's width determination.\n" <<
		" -1 - Quit.\n";


	// Infinite loop until user input is equal to -1
	bool isLooping = true;
	while (isLooping)
	{
		ChooseTaskNumber();

		// Execute choosen task
		switch (curTaskNumber)
		{
		case 5:
			ExecutionTask5();
			break;
		case 6:
			ExecutionTask6();
			break;
		case -1:
			isLooping = false;
			return;
		default:
			std::string message = "Wrong task number in TaskLoop function!\n";
			throw message;
			break;
		}

		std::cout << "Task " << curTaskNumber << " executed successfully!\n";

	}
}

void Manager::ChooseTaskNumber()
{
	std::cout << "Your input: ";
	InputValue(curTaskNumber, "Wrong input! Please input 5(tree balancing) 6(width determination) or -1(Quit).", IsCorrectTaskNumber);
}

void Manager::InputValue(int & value, const std::string & errorMessage, std::function<bool(int)> condPtr) const
{
	bool isCorrectInput = false;

	// Looping until the user input data is correct
	while (!isCorrectInput)
	{
		std::cin >> value;
		std::cin.get();

		// If еру user input is not integer value then clear all input
		if (!std::cin)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			std::cout << errorMessage << "\nYour input: ";
		}
		// If the user input does not satisfy the condition
		else if (condPtr(value))
			std::cout << errorMessage << "\nYour input: ";
		// Input is correct. End the loop
		else
			isCorrectInput = true;
	}
}


void Manager::ExecutionTask5() const
{
	std::cout << "\nTASK 5 EXECUTION\n\n"
		<< "Input size of tree (integer value in range [0, 1e6]) : ";
	
	int treeSize = -1;
	InputValue(treeSize, "Wrong input! Input integer number in range [0, 1e6]", IsInRange);

	Task5Test test(treeSize);
	test.TestFunction(treeSize);
	std::cout << "\n";
}

void Manager::ExecutionTask6() const
{
	std::cout << "\nTASK 6 EXECUTION\n\n" <<
		"Command 'opt.exe -g 5 7 bars' generate graph with 5 nodes and 7 roads and write to bars.txt\n" <<
		"Command 'opt.exe -t mars'     test graph from mars.txt\n" <<
		"Input any other string to leave Task 5!\n";
	
	std::string inputLine;

	while (std::getline(std::cin, inputLine))
	{
		// Splitting the input line using space key as the separator
		std::istringstream buf(inputLine);
		std::istream_iterator<std::string> beg(buf), end;

		std::vector<std::string> lineParts(beg, end);

		// Execute appropriate task depending on user input
		if (!lineParts.empty() && lineParts.at(0) == "opt.exe")
		{
			if (lineParts.at(1) == "-g")
				ExecuteGraphGeneration(lineParts);
			
			else if (lineParts.at(1) == "-t")
				ExecuteGraphTest(lineParts);
		}
		// If input line is not a command: quit task
		else
			return;
	}
}

void Manager::ExecuteGraphGeneration(const std::vector<std::string> & lineParts) const
{
	int citiesNumber = std::stoi(lineParts.at(2));
	int roadsNumber = std::stoi(lineParts.at(3));
	std::string fileName = lineParts.at(4);

	Generator generator(citiesNumber, roadsNumber, fileName);
	generator.GenerateRoads();
}

void Manager::ExecuteGraphTest(const std::vector<std::string>& lineParts) const
{
	std::string fileName = lineParts.at(2);

	Graph graph;
	graph.Solver(fileName);
}
