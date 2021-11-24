#pragma once
#include "Grid.h"
#include "Node.h"

class Graph
{

private:
	std::vector<Node*> nodes;

public:
	Graph();
	Graph(Grid* grid);
	~Graph();

	std::vector<Node*> getNodes();
	Node* getCurrentNodePosition(Vector2D target);
};