#pragma once

#ifndef GRAPH_H
#define GRAPH_H

#include<list>

class Graph
{
public:
	Graph(const int & nodesNumber);
	~Graph();

	void AddEdge(const int & start, const int & finish)

private:
	int nodesNumber_;
	std::list<int>* body_;
};

#endif // !GRAPH_H
