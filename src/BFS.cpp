#include "BFS.h"

BFS::BFS()
{
}

BFS::~BFS()
{
}

void BFS::CalculatePath(Agent* agent)
{
	Node* start = agent->getGraph()->getCurrentNodePosition(agent->getGraph()->pix2cell(agent->getPosition()));
	frontier.push(start);
	Node* currentNode = frontier.front();
	currentNode->comeFrom = nullptr;

	while (!frontier.empty()) {
		currentNode = frontier.front();

		if ((agent->getGraph()->cell2pix(currentNode->pos) == agent->getGoal())) 
		{
			while (!frontier.empty())
			{
				frontier.pop();
			}
			break;
		}
		
		for (Node *next : currentNode->neighbours)
		{
			if (agent->getGraph()->getCurrentNodePosition(next->pos)->comeFrom == nullptr) 
			{
				agent->getGraph()->getCurrentNodePosition(next->pos)->comeFrom = currentNode;
				frontier.push(agent->getGraph()->getCurrentNodePosition(next->pos));
			}
		}
		
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
		agent->getGraph()->getNodes()[i]->comeFrom = nullptr;
	}
}