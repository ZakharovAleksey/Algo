#include<iostream>

#include"Task_5\test\test.h"

#include"Task_6\Generator\generator.h"
#include"Task_6\Graph\graph.h"

#include<ctime>

// ����� ���� ��� �������� ������� ��������� ��������� � � 6 �� ��������� ������������ ����� ������������

// ����� ������ ������ ����������������� ���� ������ � ����� ��������� ��� ���� �����!! A->B � �� B->A ����� ����� ��������� � ���� � ����!!
int main()
{
	srand(time(NULL));

	//Task5Test test(5);
	//test.TestFunction(5);

	Generator gen(5, 7, "test");
	gen.GenerateRoads();

	Graph gr(5, 7);
	gr.GenerateGraph("test");
	gr.FindPaths(0, 3);

	return 0;
}