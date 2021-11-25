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
	currentNode->comeFrom = nullptr;
	
	std::cout << agent->pix2cell(agent->getGoal()).x  << '-' << agent->pix2cell(agent->getGoal()).y << std::endl;

	while (!frontier.empty()) {
		currentNode = frontier.front();
		frontier.pop();
		if ((agent->getGraph()->cell2pix(currentNode->pos) == agent->getGoal())) {
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
		agent->addPathPoint(agent->getGraph()->cell2pix(path[i]->pos));
	}
}