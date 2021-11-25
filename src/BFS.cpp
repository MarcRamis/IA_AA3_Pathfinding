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

	std::cout << agent->pix2cell(agent->getGoal()).x << '-' << agent->pix2cell(agent->getGoal()).y << std::endl;

	while (!frontier.empty()) {
		currentNode = frontier.front();

		if ((agent->getGraph()->cell2pix(currentNode->pos) == agent->getGoal())) 
		{
			break;
		}
		for (int i = 0; i < currentNode->neighbours.size(); i++)
		{
			if (!agent->getGraph()->getCurrentNodePosition(Vector2D(currentNode->neighbours[i]->pos.x, currentNode->neighbours[i]->pos.y))->visited)
			{
				frontier.push(agent->getGraph()->getCurrentNodePosition(Vector2D(currentNode->neighbours[i]->pos.x, currentNode->neighbours[i]->pos.y)));
				agent->getGraph()->getCurrentNodePosition(Vector2D(currentNode->neighbours[i]->pos.x, currentNode->neighbours[i]->pos.y))->visited = true;
				agent->getGraph()->getCurrentNodePosition(Vector2D(currentNode->neighbours[i]->pos.x, currentNode->neighbours[i]->pos.y))->comeFrom = currentNode;
			}
		}
		std::cout << frontier.front()->pos.x << "-" << frontier.front()->pos.y << " ";
		frontier.pop();
	}

	std::stack<Node*> path;
	while (currentNode != start) {
		path.push(currentNode);
		if (currentNode->comeFrom == nullptr)
		{
			break;
		}
		currentNode = currentNode->comeFrom;
	}

	while(path.size() != 0)
	{
		agent->addPathPoint(agent->getGraph()->cell2pix(path.top()->pos));
		path.pop();
	}
	
	for (int i = 0; i < agent->getGraph()->getNodes().size(); i++)
	{
		agent->getGraph()->getNodes()[i]->visited = false;
	}
	while (!frontier.empty())
	{
		frontier.pop();
	}
}