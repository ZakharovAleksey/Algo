#pragma once

#ifndef GRAPH_H
#define GRAPH_H

#include<vector>
#include<list>
#include<string>

class Graph
{
public:
	Graph(const int & nodesNumber, const int & relationNumber);
	~Graph();

	void GenerateGraph(const std::string & fileName);
	void FindPaths(const int & startId, const int & finishId);
	void Display() const;
	void Solver(const std::string & fileName, const int & start, const int & finish);

private:
	void AddEdge(const int & start, const int & finish, const int & width);
	// ѕереписать через указатели так как мен€ютс€
	void FindStep(const int & start, const int & finish, std::vector<bool> & isVisited, std::vector<int> & path);
	void FindMaxArmatasWidth(const std::vector<int> & curPath);
	int GetRoadWidth(const int & start, const int & finish);


	int nodesNumber_;
	int relationNumber_;
	int minWidth_;
	int maxArmatasWidth_;

	std::vector<std::list<std::pair<int, int>>> body_;
};

#endif // !GRAPH_H
