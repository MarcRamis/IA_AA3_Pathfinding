#include "Dijkstra.h"

Dijkstra::Dijkstra()
{
}

Dijkstra::~Dijkstra()
{
}

void Dijkstra::CalculatePath(Agent* agent)
{
	Node* start = agent->getGraph()->getCurrentNodePosition(agent->getGraph()->pix2cell(agent->getPosition()));
	frontier.push(start);
	Node* currentNode = frontier.top();
	currentNode->comeFrom = nullptr;

	while (!frontier.empty()) {
		currentNode = frontier.top();
		frontier.pop();

		if ((agent->getGraph()->cell2pix(currentNode->pos) == agent->getGoal()))
		{
			while (!frontier.empty())
			{
				frontier.pop();
			}
			
			break;
		}

		for (Node* next : currentNode->neighbours)
		{
			float newCost = currentNode->costSoFar + currentNode->weight;
			if (agent->getGraph()->getCurrentNodePosition(next->pos)->comeFrom == nullptr || currentNode->costSoFar > newCost)
			{
				agent->getGraph()->getCurrentNodePosition(next->pos)->costSoFar = newCost;
				agent->getGraph()->getCurrentNodePosition(next->pos)->comeFrom = currentNode;
				frontier.push(agent->getGraph()->getCurrentNodePosition(next->pos));
			}
		}

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

	while (path.size() != 0)
	{
		agent->addPathPoint(agent->getGraph()->cell2pix(path.top()->pos));
		path.pop();
	}

	agent->getGraph()->Reset();
}
