#include"graph.h"

Graph::Graph(const int & nodesNumber) : nodesNumber_(nodesNumber), body_(new std::list<int>(nodesNumber_)) {}

Graph::~Graph() {}

void Graph::AddEdge(const int & start, const int & finish)
{
	body_[start].push_back(finish);
}
