#include "BFS.h"

BFS::BFS()
{
}

BFS::~BFS()
{
}

void BFS::CalculatePath(Agent* agent)
{
	Node* start = agent->getGraph()->getCurrentNodePosition(agent->getGraph()->pix2cell(agent->getPosition())); // Acces to first node in graph
	frontier.push(start);
	Node* currentNode = frontier.front();
	currentNode->visited = true;
	
	while (!frontier.empty()) {
		currentNode = frontier.front();
		frontier.pop();
		if (currentNode->pos == agent->getGoal()) {
			break;
		}
		for (int i = 0; i < currentNode->neighbours.size(); i++)
		{
			if (!currentNode->neighbours[i]->visited)
			{
				frontier.push(currentNode->neighbours[i]);
				currentNode->neighbours[i]->visited = true;	
				currentNode->neighbours[i]->comeFrom = currentNode;
			}
		}
	}

	std::vector<Node*> path;
	while (currentNode != start) {
		path.push_back(currentNode);
		currentNode = currentNode->comeFrom;
	}

	for (int i = 0; i < path.size(); i++)
	{
		agent->addPathPoint(path[i]->pos);
	}
}