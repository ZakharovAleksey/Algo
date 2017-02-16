#include"graph.h"

#include<fstream>
#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>
#include<queue>
#include<map>

// Finds index of node with the biggest width from all not visited yet nodes
int FindNodeWithMaxWidth(const std::vector<int> & width, const std::vector<bool> & isVisited, const int & minWidth)
{
	int curNodeId = -1, curMaxWidth = minWidth;

	for (int i = 0; i < width.size(); ++i)
	{
		if (!isVisited.at(i) && width.at(i) > curMaxWidth)
		{
			curMaxWidth = width.at(i);
			curNodeId = i;
		}
	}

	return curNodeId;
}

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
		// If we are using constructor by default with no parameters, we need to obtain and number
		// of nodes, number of conditions and allocate memory for graph's body
		in >> nodesNumber_ >> relationNumber_;
		in.get();

		if(body_.empty())
			body_.resize(nodesNumber_);


		// Set default values for graph edge
		int start = -1;
		int finish = -1;
		int width = -1;

		// Read edges from the file and add them to graph
		for(int j = 0; j < relationNumber_; ++j)
		{
			in >> start >> finish >> width;

			AddEdge(start, finish, width);
			// Find minimum width (It must not change after the tank travel, in accordance with the task)
			minWidth_ = std::min(minWidth_, width);
		}
	}
	else
	{
		in.close();

		std::string message = "Could not open file " + fileName + ".txt to read data to graph!\n";
		throw message;
	}
}

void Graph::FindPaths(const int & startId, const int & finishId)
{
	std::vector<bool> isVisited(nodesNumber_, false);
	std::vector<int> path;

	// Recursive function which pind all possible paths from 'startId' node to 'finishId' node
	//FindStep(startId, finishId, isVisited, path);

	// Function finds maximum possible width using BFS
	BFSFindMaxWidth(startId, finishId);

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

		//for (auto i : path)
		//	std::cout << i << " -> ";
		//std::cout << std::endl;

		// Obtain maximum possible Armata's Width, in a way that tank could use this way and
		// the minimul width did not change
		FindMaxArmatasWidth(path);
	}
	else
	{
		std::list<std::pair<int, int>>::iterator i;

		// Looping through all possible steps from current node and if it is possible to
		// visit one - go there
		for(i = body_.at(start).begin(); i != body_.at(start).end(); ++i )
			if(!isVisited.at(i->first) && i->second > minWidth_)
				FindStep(i->first, finish, isVisited, path);
		
	}

	// If this is a dead end, take a step back
	path.pop_back();
	isVisited.at(start) = false;
}

void Graph::BFSFindMaxWidth(const int & startId, const int & finishId)
{
	// Initial value of width for all nodes
	int minWidth = -100;
	std::vector<bool> isVisited(nodesNumber_, false);
	// Store maximum width from start node to current
	std::vector<int> width(nodesNumber_, minWidth);

	width.at(startId) = 0;

	for (int curNode = 0; curNode < nodesNumber_; curNode++)
	{
		// Index of node with the biggest width from all not visited yet nodes
		int stepFromId = FindNodeWithMaxWidth(width, isVisited, minWidth);

		if (stepFromId != -1)
		{
			// Set node as visited
			isVisited.at(stepFromId) = true;

			std::list<std::pair<int, int>>::iterator it;
			// Looping through all the neighbours of the current node
			for (it = body_.at(stepFromId).begin(); it != body_.at(stepFromId).end(); ++it)
			{
				// If we could go to this neighbor
				if (!isVisited.at(it->first) && GetRoadWidth(stepFromId, it->first) > minWidth_)
				{
					// If this node is the finish node
					if (it->first == finishId)
					{
						// If we get to the finish node from the start by single step:
						// finish node width is equal to (width of the road - minimum road width)
						if (width.at(stepFromId) == 0)
							width.at(it->first) = GetRoadWidth(stepFromId, it->first) - minWidth_;
						// Obtain maximum from all possible widths
						width.at(it->first) = std::max(std::min(GetRoadWidth(stepFromId, it->first) - minWidth_, width.at(stepFromId)), width.at(it->first));
					}
					// If we start from start node - width of it's neighbours
					// is equal to (width of the road - minimum road width)
					if (stepFromId == startId)
						width.at(it->first) = GetRoadWidth(stepFromId, it->first) - minWidth_;
					// If node is not finised node, it's width is equal to
					// minimum from (width of the road - minimum road width) and width of 'stepFromId' node
					else if (it->first != finishId)
					{
						width.at(it->first) = std::min(GetRoadWidth(stepFromId, it->first) - minWidth_, width.at(stepFromId));
					}
				}
			}
		}
	}

	maxArmatasWidth_ = width.at(finishId);
}

void Graph::FindMaxArmatasWidth(const std::vector<int>& curPath)
{
	// Find maximum possible Armatas width on current path
	int maxWidth = 100;

	// Looping through all the path, and calculate maximum possible Armatas width on this path
	for (int startId = 0; startId < curPath.size() - 1; ++startId)
	{
		int finishId = startId + 1;
		maxWidth = std::min(maxWidth, GetRoadWidth(curPath.at(startId), curPath.at(finishId)) - minWidth_);
	}

	// Checks if on current path maximum Armata's width is bigger than current Armata's width
	maxArmatasWidth_ = std::max(maxWidth, maxArmatasWidth_);
}

int Graph::GetRoadWidth(const int & start, const int & finish)
{
	for (auto & i : body_.at(start))
	{
		if (i.first == finish)
			return i.second;
	}

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

	std::cout << "Minimum width = " << minWidth_ << std::endl;
}

void Graph::Solver(const std::string & fileName)
{
	// Generate graph using data from 'fileName' file
	GenerateGraph(fileName);

	// Capital city Id = 0
	int start = 0;
	// Zodanga city Id = nodesNumber - 2
	int finish = nodesNumber_ - 1;

	if (nodesNumber_ == 0 || relationNumber_ == 0)
	{
		std::cout << "No such path is avalible!\n";
		maxArmatasWidth_ = 0;
		return;
	}

	FindPaths(start, finish);
}
