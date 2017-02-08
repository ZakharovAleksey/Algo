#include<iostream>

//#include"Task_5\test\test.h"
//
//#include"Task_6\Generator\generator.h"
//#include"Task_6\Graph\graph.h"

#include"Manager\manager.h"

#include<ctime>

// Нужен бдет еще менеджер который управляет задиниями а в 6 он проверяет корректность ввода пользователя

// Чтобы делать дороги двухнаправленными надо просто в графе добавлять два пути сразу!! A->B и из B->A тогда может двигаться и туда и туда!!!
int main()
{
	srand(time(NULL));

	try
	{
		Manager manage;
		manage.TaskLoop();
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