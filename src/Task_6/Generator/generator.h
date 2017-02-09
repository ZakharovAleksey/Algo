#pragma once

#ifndef GENERATOR_H
#define GENERATOR_H

#include<string>
#include<vector>

#include<memory>

/// <summary>
/// Generator class implementation.
/// Performs generation of the map, including cities and roads between them.
/// </summary>
class Generator
{
public:

	/// <summary>
	/// Structure holds all information about the road between the cities pair.
	/// </summary>
	struct Condition
	{
		// Index of the city at which road starts
		int startId;
		// Index of the city at which road finishes
		int finishId;
		// Width of the road
		int width;

		Condition() : startId(0), finishId(0), width(0) {}
		Condition(int startId, int finishId, int weight) : startId(startId), finishId(finishId), width(weight) {}
	};

	Generator(int citiesNumber, int roadsNumber, std::string outFileName);
	~Generator();

	/// <summary>
	/// Performs the road generation depending on number of cities and number of roads between them.
	/// </summary>
	void GenerateRoads();

private:
	// Number of cities on the map
	int citiesNumber_;
	// Number of roads on the map
	int roadsNumber_;
	// Name of file in which generated data would be written
	std::string outFileName_;

	/// <summary>
	/// Adds a new condition 'curCondition' to the 'conditions' vector.
	/// </summary>
	/// <param name="conditions"> Vector in which 'condition' value would be added. </param>
	/// <param name="curCondition"> Condition to be copied (or moved) 'conditions' vector. </param>
	void AddCondition(std::vector<Condition>* conditions, Condition* curCondition) const ;
	/// <summary>
	/// Fills condition vector 'conditions' with all possible conditions if graph is connected.
	/// </summary>
	/// <param name="conditions">  Vector in which 'condition' value would be added. </param>
	/// <param name="curCondition"> Condition to be copied (or moved) 'conditions' vector. </param>
	void FillConnectedGraph(std::vector<Condition>* conditions, Condition* curCondition);
};


#endif // !GENERATOR_H
