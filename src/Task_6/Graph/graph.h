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
	void FindPaths(int startId, int secondId);

	void Display() const;


private:
	void AddEdge(const int & start, const int & finish, const int & width);
	// ѕереписать через указатели так как мен€ютс€
	void findStep(const int & start, const int & finish, std::vector<bool> & isVisited, std::vector<int> & path);


	int nodesNumber_;
	int relationNumber_;
	std::vector<std::list<std::pair<int, int>>> body_;
};

#endif // !GRAPH_H
