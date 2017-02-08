#include"graph.h"

#include<fstream>
#include<iostream>
#include<algorithm>


Graph::Graph(const int & nodesNumber, const int & relationNumber) : 
	nodesNumber_(nodesNumber), relationNumber_(relationNumber), 
	minWidth_(100), maxArmatasWidth_(100)
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
			minWidth_ = std::min(minWidth_, width);
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

		FindMaxArmatasWidth(path);

		/*for (int i = 0; i < path.size() - 1; ++i)
		{
			int j = i + 1;
			std::cout << "Width " << path.at(i) << " -> " << path.at(j) << " = " << getWidth(path.at(i), path.at(j)) << std::endl;
			maxArmatasWidth_ = std::min(maxArmatasWidth_, getWidth(path.at(i), path.at(j)) - minWidth_);
			std::cout << "now maxArmatasWidth_ = " << maxArmatasWidth_ << std::endl;
		}*/

	}
	else
	{
		std::list<std::pair<int, int>>::iterator i;

		for(i = body_.at(start).begin(); i != body_.at(start).end(); ++i )
			if(!isVisited.at(i->first) && i->second > minWidth_)
				findStep(i->first, finish, isVisited, path);
		
	}

	path.pop_back();
	isVisited.at(start) = false;
}

void Graph::FindMaxArmatasWidth(const std::vector<int>& curPath)
{
	for (int i = 0; i < curPath.size() - 1; ++i)
	{
		int j = i + 1;
		std::cout << "Width " << curPath.at(i) << " -> " << curPath.at(j) << " = " << getWidth(curPath.at(i), curPath.at(j)) << std::endl;
		maxArmatasWidth_ = std::min(maxArmatasWidth_, getWidth(curPath.at(i), curPath.at(j)) - minWidth_);
		std::cout << "now maxArmatasWidth_ = " << maxArmatasWidth_ << std::endl;
	}
}

int Graph::getWidth(const int & start, const int & finish)
{
	for (auto & i : body_.at(start))
	{
		if (i.first == finish)
			return i.second;
	}
	std::cout << "WRONG IN getWIdth!\n";
	return -1;
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
	std::cout << "min width = " << minWidth_ << std::endl;
}
