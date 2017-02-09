#include"Manager\manager.h"

#include<iostream>
#include<ctime>

int main()
{
	srand(time(NULL));

	try
	{
		// Start manager
		Manager manager;
		manager.TaskLoop();
	}
	catch (const std::exception & message)
	{
		std::cout << message.what();
	}
	catch (std::string & message)
	{
		std::cout << message;
	}
	catch (...)
	{
		std::cout << "Unknown exception!\n";
	}

	return 0;
}