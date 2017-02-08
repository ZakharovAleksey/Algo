#include<iostream>

#include"Task_5\test\test.h"

#include"Task_6\Generator\generator.h"

#include<ctime>

// Нужен бдет еще менеджер который управляет задиниями а в 6 он проверяет корректность ввода пользователя
int main()
{
	srand(time(NULL));

	//Task5Test test(5);
	//test.TestFunction(5);

	Generator gen(5, 7, "test");
	gen.GenerateRoads();

	return 0;
}