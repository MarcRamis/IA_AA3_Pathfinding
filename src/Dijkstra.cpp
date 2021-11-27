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
	currentWeight = 0;
	frontier.push(start);
	Node* currentNode = frontier.top();
	currentNode->visited = true;

	while (!frontier.empty()) {
		currentNode = frontier.top();

		if ((agent->getGraph()->cell2pix(currentNode->pos) == agent->getGoal()))
		{
			while (!frontier.empty())
			{
				frontier.pop();
			}
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

	while (path.size() != 0)
	{
		agent->addPathPoint(agent->getGraph()->cell2pix(path.top()->pos));
		path.pop();
	}

	for (int i = 0; i < agent->getGraph()->getNodes().size(); i++)
	{
		agent->getGraph()->getNodes()[i]->visited = false;
	}
	//
	//while (!frontier.empty()) {
	//	currentNode = frontier.top();
	//
	//	if ((agent->getGraph()->cell2pix(currentNode->pos) == agent->getGoal()))
	//	{
	//		//break;
	//		////// Repetir hasta encontrar el camino más óptimo
	//		currentWeight = 0;
	//		Node* tempNode = currentNode;
	//		while (tempNode != start)
	//		{
	//			currentWeight += currentNode->weight;
	//			tempNode = tempNode->comeFrom;
	//		}
	//
	//		if (currentWeight < costSoFar)
	//		{
	//			while (path.size() != 0)
	//			{
	//				while (!frontier.empty())
	//				{
	//					frontier.pop();
	//				}
	//				path.pop();
	//			}
	//			costSoFar = currentWeight;
	//			while (currentNode != start) {
	//				path.push(currentNode);
	//				if (currentNode->comeFrom == nullptr)
	//				{
	//					break;
	//				}
	//				currentNode = currentNode->comeFrom;
	//			}
	//		}
	//		frontier.pop();
	//		//////
	//	}
	//	for (int i = 0; i < currentNode->neighbours.size(); i++)
	//	{
	//		if (!agent->getGraph()->getCurrentNodePosition(Vector2D(currentNode->neighbours[i]->pos.x, currentNode->neighbours[i]->pos.y))->visited)
	//		{
	//			frontier.push(agent->getGraph()->getCurrentNodePosition(Vector2D(currentNode->neighbours[i]->pos.x, currentNode->neighbours[i]->pos.y)));
	//			agent->getGraph()->getCurrentNodePosition(Vector2D(currentNode->neighbours[i]->pos.x, currentNode->neighbours[i]->pos.y))->visited = true;
	//			agent->getGraph()->getCurrentNodePosition(Vector2D(currentNode->neighbours[i]->pos.x, currentNode->neighbours[i]->pos.y))->comeFrom = currentNode;
	//		}
	//	}
	//	std::cout << frontier.top()->pos.x << "-" << frontier.top()->pos.y << " " << frontier.top()->weight << std::endl;
	//	frontier.pop();
	//}
	//std::cout << std::endl << "////////////////////" << std::endl;
	//for (int i = 0; i < frontier.size(); i++)
	//{
	//	std::cout << frontier.top()->pos.x << "-" << frontier.top()->pos.y << " " << frontier.top()->weight << std::endl;
	//	frontier.pop();
	//}
	//
	//
	//
	//while (path.size() != 0)
	//{
	//	agent->addPathPoint(agent->getGraph()->cell2pix(path.top()->pos));
	//	path.pop();
	//}
	//
	//for (int i = 0; i < agent->getGraph()->getNodes().size(); i++)
	//{
	//	agent->getGraph()->getNodes()[i]->visited = false;
	//}
	//
	//costSoFar = 1000000;
}
