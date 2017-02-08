#include<iostream>

#include"Task_5\test\test.h"

#include"Task_6\Generator\generator.h"
#include"Task_6\Graph\graph.h"

#include<ctime>

// ����� ���� ��� �������� ������� ��������� ��������� � � 6 �� ��������� ������������ ����� ������������

// ����� ������ ������ ����������������� ���� ������ � ����� ��������� ��� ���� �����!! A->B � �� B->A ����� ����� ��������� � ���� � ����!!!
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