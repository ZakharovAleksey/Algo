#include"manager.h"

#include<limits>
#include <iterator>
#include <sstream>

int kWrongInput = -100;

Manager::Manager() {}

Manager::~Manager() {}

void Manager::TaskLoop()
{
	std::cout << "WELCOME TO HUAWEI TASK SOLVER!\n\n" <<
		"Input number of choosen task:\n" <<
		"  5 - Checking whether a tree is balanced.\n" <<
		"  6 - Armata's width determination.\n" <<
		" -1 - Quit.\n";

	bool isExecuted = true;

	while (isExecuted)
	{
		ChooseTaskNumber();

		switch (curTaskNumber)
		{
		case 5:
			ExecutionTask5();
			break;
		case 6:
			ExecutionTask6();
			break;
		case -1:
			return;
		default:
			break;
		}

	}

	


}

void Manager::ChooseTaskNumber()
{
	bool isCorrectInput = false;

	while (!isCorrectInput)
	{
		std::cout << "Your input: ";
		std::cin >> curTaskNumber;

		if (!std::cin)
		{
			// Clear all user input
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			std::cout << "Wrong input! Please input 5(tree balancing) 6(width determination) or -1(Quit).\nYour input:  ";
			continue;
		}

		if (curTaskNumber == 5 || curTaskNumber == 6 || curTaskNumber == -1)
			isCorrectInput = true;
		else
			std::cout << "Wrong input! Please input 5(tree balancing) 6(width determination) or -1(Quit).\nYour input:  ";
	}
}

void Manager::ExecutionTask5() const
{
	std::cout << "\nTASK 5 EXECUTION\n\n"
		<< "Inut tree size in range [0, 1e6]: ";
	
	int treeSize = -1;
	InputValue(treeSize, "Wrong input! Input number in range [0, 1e6]");

	Task5Test test(treeSize);
	test.TestFunction(treeSize);
	std::cout << "\n";
}

void Manager::InputValue(int & value, const std::string & errorMessage) const
{
	bool isCorrectInput = false;

	while (!isCorrectInput)
	{
		std::cin >> value;

		if (!std::cin)
		{
			// Clear all user input
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			std::cout << errorMessage << "\nYour input: ";
		}
		else if (value < 0 || value > int(1e6))
			std::cout << errorMessage << "\nYour input: ";
		else
			isCorrectInput = true;
	}
}

void Manager::ExecutionTask6() const
{
	int citiesNumber = -1;
	int roadsNumber = -1;
	std::string fileName;

	std::cout << "\nTASK 6 EXECUTION\n\n" <<
		"Input string in format: 'opt.exe -g 20 100 bars' to generate graph with 20 nodes and 100 roads and write to bars.txt\n" <<
		"Input string in format: 'opt.exe -t mars'    to test graph from mars.txt\n" <<
		"Input any other string to leave Task 5!\n";
	
	std::string inputLine;
	std::cin.get();

	while (std::getline(std::cin, inputLine))
	{
		// Splitting the input line
		std::istringstream buf(inputLine);
		std::istream_iterator<std::string> beg(buf), end;

		std::vector<std::string> parts(beg, end);

		if (parts.at(0) == "opt.exe")
		{
			if (parts.at(1) == "-g")
			{
				citiesNumber = std::stoi(parts.at(2));
				roadsNumber = std::stoi(parts.at(3));
				fileName = parts.at(4);

				Generator generator(citiesNumber, roadsNumber, fileName);
				generator.GenerateRoads();
			}
			else if (parts.at(1) == "-t")
			{
				fileName = parts.at(2);

				std::cout << "!-> " << fileName << std::endl;

				Graph gr;
				std::cout << "created\n";
				gr.Solver(fileName);
			}
		}
		else
			return;
	}
}
