#include"graph.h"

#include<fstream>
#include<iostream>

Graph::Graph(const int & nodesNumber, const int & relationNumber) : nodesNumber_(nodesNumber), relationNumber_(relationNumber)
{
	body_.resize(nodesNumber_);
}

Graph::~Graph() {}

void Graph::AddEdge(const int & start, const int & finish, const int & width)
{
	body_[start].push_back(std::make_pair(finish, width));
}


void Graph::GenerateGraph(const std::string & fileName)
{
	std::ifstream in;

	in.open(fileName + ".txt");

	if (in.is_open())
	{
		int start = -1;
		int finish = -1;
		int width = -1;

		for(int j = 0; j < relationNumber_; ++j)
		{
			in >> start >> finish >> width;
			AddEdge(start, finish, width);
		}
		Display();
	}
	else
	{
		std::string message = "Could not open file " + fileName + ".txt to read data to graph!\n";
		throw message;
	}
}

void Graph::FindPaths(int startId, int finishId)
{
	std::vector<bool> isVisited(nodesNumber_, false);
	std::vector<int> path;

	findStep(startId, finishId, isVisited, path);
}

void Graph::findStep(const int & start, const int & finish, std::vector<bool>& isVisited, std::vector<int>& path)
{
	isVisited.at(start) = true;
	path.push_back(start);

	if (start == finish)
	{
		for (auto i : path)
			std::cout << i << " --> ";
		std::cout << std::endl;
	}
	else
	{
		std::list<std::pair<int, int>>::iterator i;

		for(i = body_.at(start).begin(); i != body_.at(start).end(); ++i )
			if(!isVisited.at(i->first))
				findStep(i->first, finish, isVisited, path);
		
	}

	path.pop_back();
	isVisited.at(start) = false;
}

void Graph::Display() const
{
	for (int i = 0; i < nodesNumber_; ++i)
	{
		std::cout << i << ": ";
		for (auto j : body_[i])
			std::cout << j.first << " (" << j.second << ") -> ";
		std::cout << std::endl;
	}
}
