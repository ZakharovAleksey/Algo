#include"generator.h"

#include<iostream>

#include<cstdlib>
#include<fstream>

#include<algorithm>

// Запихнкть в Static class!!!!!!!
int kMinRoadWigth = 1;
int kMaxRoadWigth = 100;


// Return true if condition 'item' already exist in 'vec'
bool IsInConditions(std::vector<Generator::Condition> const & vec, Generator::Condition const & item)
{
	for (auto & i : vec)
		if (( i.startId == item.startId && i.finishId == item.finishId) //) ТУТУ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 
			||  ( i.finishId == item.startId && i.startId == item.finishId))
			return true;

	return false;	
}


Generator::Generator(int citiesNumber, int roadsNumber, std::string outFileName) :
	citiesNumber_(citiesNumber), roadsNumber_(roadsNumber), outFileName_(outFileName) 
{ }

Generator::~Generator() {}

void Generator::GenerateRoads()
{
	std::ofstream out; out.open(outFileName_ + ".txt");

	std::vector<Condition> conditions;
	Condition curCondition;
	
	if (out.is_open())
	{
		// If graph is connected
		if (roadsNumber_ > citiesNumber_ * (citiesNumber_ - 1) / 2)
		{
			FillConnectedGraph(&conditions, &curCondition);
		}
		else
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
		}

		// Write in the file number of cities and number of roads
		out << citiesNumber_ << " " << roadsNumber_ << std::endl;

		// Write generated conditions in the file
		for (auto & i : conditions)
		{
			out << i.startId << " " << i.finishId << " " << i.width << std::endl;
			std::cout << i.startId << " " << i.finishId << " " << i.width << std::endl;
		}
	}
	else
	{
		out.close();

		std::string message = "Could not open file " + outFileName_ + ".txt for writing!\n";
		throw message;
	}

	out.close();
}

void Generator::AddCondition(std::vector<Condition>* conditions, Condition* curCondition) const
{
	// Random generation of cities Id and width of the road between them
	curCondition->startId = rand() % citiesNumber_;
	curCondition->finishId = rand() % citiesNumber_;
	curCondition->width = kMinRoadWigth + rand() % (kMaxRoadWigth - kMinRoadWigth);


	// Check that it is different cities and that condition of this type is already exist
	while (curCondition->finishId == curCondition->startId || IsInConditions(*conditions, *curCondition))
	{
		curCondition->startId = rand() % citiesNumber_;
		curCondition->finishId = rand() % citiesNumber_;
	}

	if (curCondition->finishId < curCondition->startId)
	{
		std::swap(curCondition->finishId, curCondition->startId);
	}

	std::cout << curCondition->startId << " " << curCondition->finishId << std::endl;

	conditions->push_back(*curCondition);
}

void Generator::FillConnectedGraph(std::vector<Condition>* conditions, Condition * curCondition)
{
	roadsNumber_ = citiesNumber_ * (citiesNumber_ - 1) /2;

	for (int i = 0; i < citiesNumber_; ++i)
		for (int j = 0; j < citiesNumber_; ++j)
		{
			if (i != j)
			{
				curCondition->startId = i;
				curCondition->finishId = j;
				curCondition->width = kMinRoadWigth + rand() % (kMaxRoadWigth - kMinRoadWigth);

				conditions->push_back(*curCondition);
			}
		}
}

