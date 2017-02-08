#include<iostream>

//#include"Task_5\test\test.h"
//
//#include"Task_6\Generator\generator.h"
//#include"Task_6\Graph\graph.h"

#include"Manager\manager.h"

#include<ctime>

// ����� ���� ��� �������� ������� ��������� ��������� � � 6 �� ��������� ������������ ����� ������������

// ����� ������ ������ ����������������� ���� ������ � ����� ��������� ��� ���� �����!! A->B � �� B->A ����� ����� ��������� � ���� � ����!!!
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