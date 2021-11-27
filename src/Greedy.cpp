#include "Greedy.h"

Greedy::Greedy()
{
}

Greedy::~Greedy()
{
}

void Greedy::CalculatePath(Agent* agent)
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
			if (agent->getGraph()->getCurrentNodePosition(next->pos)->comeFrom == nullptr)
			{
				agent->getGraph()->getCurrentNodePosition(next->pos)->heuristic = ManhattanDistance(agent->getGraph()->pix2cell(agent->getGoal()), agent->getGraph()->getCurrentNodePosition(next->pos)->pos);
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

float Greedy::ManhattanDistance(Vector2D& n1, Vector2D& n2)
{
	return (abs(n1.x - n2.x) + abs(n1.y - n2.y));
}
