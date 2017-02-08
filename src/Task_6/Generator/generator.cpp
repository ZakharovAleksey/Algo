#include"generator.h"

#include<iostream>

#include<cstdlib>
#include<fstream>

#include<algorithm>

// «апихнкть в Static class!!!!!!!
int kMinRoadWigth = 1;
int kMaxRoadWigth = 100;


// Return true if condition 'item' already exist in 'vec'
bool IsInConditions(std::vector<Generator::Condition> const & vec, Generator::Condition const & item)
{
	for (auto & i : vec)
		if (( i.startId == item.startId && i.finishId == item.finishId) || 
			( i.finishId == item.startId && i.startId == item.finishId))
			return true;

	return false;	
}


Generator::Generator(int citiesNumber, int roadsNumber, std::string outFileName) :
	citiesNumber_(citiesNumber), roadsNumber_(roadsNumber), outFileName_(outFileName) { }

Generator::~Generator() {}

void Generator::GenerateRoads()
{
	std::ofstream out; out.open(outFileName_ + ".txt");

	std::vector<Condition> conditions;
	Condition curCondition;
	
	if (out.is_open())
	{
		// Add conditions
		for (int roadId = 0; roadId < roadsNumber_; ++roadId)
			AddCondition(&conditions, &curCondition);

		// Sort them on the start city Id for future convenience
		std::sort(conditions.begin(), conditions.end(),
			[](const Condition & a, const Condition & b) -> bool
		{
			return a.startId < b.startId;
		});

		// Write them in file
		for (auto & i : conditions)
		{
			out << i.startId << " " << i.finishId << " " << i.width << std::endl;
			std::cout << i.startId << " " << i.finishId << " " << i.width << std::endl;
		}
		std::cout << "-------------" << std::endl;
	}
	else
	{
		out.close();

		std::string message = "Could not open file " + outFileName_ + ".txt for writing!\n";
		throw message;
	}

	out.close();
}

void Generator::AddCondition(std::vector<Condition>* conditions, Condition* curCondition)
{
	// „то-то не то с генерацией условий! последний город на нег нет св€зей никогда!!!!!!


	// Random generation of cities Id and width of the road between them (+1 for using last city)
	curCondition->startId = rand() % citiesNumber_;// +1;
	curCondition->finishId = rand() % citiesNumber_;// +1;
	curCondition->width = kMinRoadWigth + rand() % (kMaxRoadWigth - kMinRoadWigth);

	// Check that it is different cities and that condition of this type is already exist
	while (curCondition->finishId == curCondition->startId || IsInConditions(*conditions, *curCondition))
	{
		curCondition->finishId = rand() % citiesNumber_;
	}
	// Swap for future convenience
	if (curCondition->startId > curCondition->finishId)
		std::swap(curCondition->startId, curCondition->finishId);

	conditions->push_back(*curCondition);
}

