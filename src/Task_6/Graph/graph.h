#pragma once

#ifndef GRAPH_H
#define GRAPH_H

#include<vector>
#include<list>
#include<string>

class Graph
{
public:
	Graph();
	Graph(const int & nodesNumber, const int & relationNumber);
	~Graph();

	/// <summary>
	/// Generates graph in accordance with conditions from 'fileName' file.
	/// </summary>
	/// <param name="fileName"> Name of file which store the conditions between the nodes of graph. </param>
	void GenerateGraph(const std::string & fileName);
	/// <summary>
	/// Finds all the paths from node with 'startId' index to node with 'finishId' index.
	/// </summary>
	/// <param name="startId"></param>
	/// <param name="finishId"></param>
	void FindPaths(const int & startId, const int & finishId);
	/// <summary>
	/// Displays the generated graph on the console screen.
	/// </summary>
	void Display() const;
	/// <summary>
	/// Peforms the solution of foundation maximum possible Armata's wigth.
	/// </summary>
	/// <param name="fileName"> Name of file which store the conditions between the nodes of graph. </param>
	void Solver(const std::string & fileName);

private:

	/// <summary>
	/// Adding new edge between nodes with 'startEd' and 'finishEd' indexes.
	/// </summary>
	/// <param name="start"> Index of first node. </param>
	/// <param name="finish"> Index of second node. </param>
	/// <param name="width"> Width of the current edge. </param>
	void AddEdge(const int & start, const int & finish, const int & width);
	/// <summary>
	/// Finds next possible step from node with 'start' and if this stepp leed to 'finish' node displays path.
	/// </summary>
	/// <param name="start"> Index of the starting node. </param>
	/// <param name="finish"> Index of the last node. </param>
	/// <param name="isVisited"> Vector which contains true values if this node already visited on this path, false values otherwise. </param>
	/// <param name="path"> Vector which stores curernt path. </param>
	void FindStep(const int & start, const int & finish, std::vector<bool> & isVisited, std::vector<int> & path);
	/// <summary>
	/// Calculates maximum possible Armata's width on the current path 'curPath'.
	/// </summary>
	/// <param name="curPath"> Current path leading from start node to finish node. </param>
	void FindMaxArmatasWidth(const std::vector<int> & curPath);
	/// <summary>
	/// Gets width of the edge connecting node with 'start' index and node with 'finish' index.
	/// </summary>
	/// <param name="start"> Index of the edges beginning.</param>
	/// <param name="finish"> Index of the edges ending. </param>
	/// <returns></returns>
	int GetRoadWidth(const int & start, const int & finish);

	// Number of the nodes in graph
	int nodesNumber_;
	// Number of the conditions in graph
	int relationNumber_;
	// Minimum width of the edge in the graph
	int minWidth_;
	// Maximum possible Armata's width
	int maxArmatasWidth_;

	
	typedef std::vector<std::list<std::pair<int, int>>> GraphBody;
	// Graph body (contains pair = (index of finish node and width of the road)
	GraphBody body_;
};

#endif // !GRAPH_H
