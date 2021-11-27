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

	Vector2D cell2pix(Vector2D cell);
	Vector2D pix2cell(Vector2D pix);
	
	float GetCost(Node *n1, Node* n2);
};