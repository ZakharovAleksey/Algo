#include"graph.h"

#include<fstream>
#include<iostream>
#include<algorithm>


Graph::Graph() :
	nodesNumber_(0), relationNumber_(0),
	minWidth_(100), maxArmatasWidth_(0) 
{}

Graph::Graph(const int & nodesNumber, const int & relationNumber) :
	nodesNumber_(nodesNumber), relationNumber_(relationNumber), 
	minWidth_(100), maxArmatasWidth_(0)
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
		in >> nodesNumber_ >> relationNumber_;
		in.get();

		if(body_.empty())
			body_.resize(nodesNumber_);

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

void Graph::FindPaths(const int & startId, const int & finishId)
{
	std::vector<bool> isVisited(nodesNumber_, false);
	std::vector<int> path;

	FindStep(startId, finishId, isVisited, path);

	if (maxArmatasWidth_ == 0)
		std::cout << "No such path is avalible!\n";
	else
		std::cout << "Max possible Armatas width: " << maxArmatasWidth_ << std::endl;
}

void Graph::FindStep(const int & start, const int & finish, std::vector<bool>& isVisited, std::vector<int>& path)
{
	isVisited.at(start) = true;
	path.push_back(start);

	if (start == finish)
	{
		// If we here, than we find path from start to finish
		for (auto i : path)
			std::cout << i << " -> ";
		std::cout << std::endl;
		// Now we find maximum possible Armatas Width, чтобы танк смог проити по этому пути 
		FindMaxArmatasWidth(path);
	}
	else
	{
		std::list<std::pair<int, int>>::iterator i;

		for(i = body_.at(start).begin(); i != body_.at(start).end(); ++i )
			if(!isVisited.at(i->first) && i->second > minWidth_)
				FindStep(i->first, finish, isVisited, path);
		
	}

	path.pop_back();
	isVisited.at(start) = false;
}

void Graph::FindMaxArmatasWidth(const std::vector<int>& curPath)
{
	// Find maximum possible Armatas width on current path
	int maxWidth = 100;

	for (int startId = 0; startId < curPath.size() - 1; ++startId)
	{
		int finishId = startId + 1;
		maxWidth = std::min(maxWidth, GetRoadWidth(curPath.at(startId), curPath.at(finishId)) - minWidth_);
	}

	// And now we chek if on curren road max possible width os bigger
	maxArmatasWidth_ = std::max(maxWidth, maxArmatasWidth_);
}

int Graph::GetRoadWidth(const int & start, const int & finish)
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

void Graph::Solver(const std::string & fileName)
{
	GenerateGraph(fileName);

	int start = 0;
	int finish = nodesNumber_ - 2;

	FindPaths(start, finish);
}
