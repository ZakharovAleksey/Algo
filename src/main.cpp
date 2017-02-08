#include<iostream>

#include"Task_5\test\test.h"

#include"Task_6\Generator\generator.h"
#include"Task_6\Graph\graph.h"

#include<ctime>

// Нужен бдет еще менеджер который управляет задиниями а в 6 он проверяет корректность ввода пользователя

// Чтобы делать дороги двухнаправленными надо просто в графе добавлять два пути сразу!! A->B и из B->A тогда может двигаться и туда и туда!!!
int main()
{
	srand(time(NULL));

	//Task5Test test(5);
	//test.TestFunction(5);


	int citiesNumber = 5;
	int roadsNumber = 7;
	std::string outFileName = "test";

	Generator gen(citiesNumber, roadsNumber, outFileName);
	gen.GenerateRoads();

	Graph gr(citiesNumber, roadsNumber);
	gr.Solver(outFileName, 0, 3);

	return 0;
}