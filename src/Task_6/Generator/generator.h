#pragma once

#ifndef GENERATOR_H
#define GENERATOR_H

#include<string>
#include<vector>

#include<memory>

class Generator
{
public:

	struct Condition
	{
		int startId;
		int finishId;
		int width;

		Condition() : startId(0), finishId(0), width(0) {}
		Condition(int startId, int finishId, int weight) : startId(startId), finishId(finishId), width(weight) {}
	};

	Generator(int citiesNumber, int roadsNumber, std::string outFileName);
	~Generator();

	void GenerateRoads();

private:
	int citiesNumber_;
	int roadsNumber_;
	std::string outFileName_;


	void AddCondition(std::vector<Condition>* conditions, Condition* /*const std::unique_ptr<std::vector<Condition>> & conditions, std::unique_ptr<Condition>*/ curCondition);
};


#endif // !GENERATOR_H
