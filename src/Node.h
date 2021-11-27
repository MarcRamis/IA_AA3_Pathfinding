#pragma once
#include "Vector2D.h"

#include <vector>

class Node
{
private:

public:

	Vector2D pos;
	std::vector<Node*> neighbours;
	float weight = 0;
	float costSoFar = 0;
	float heuristic = 0;

	Node* comeFrom;

	Node();
	Node(Vector2D _pos, float _weight);
	Node(Vector2D _pos, std::vector<Node*> _neighbours, float _weight);
	~Node();

	bool operator()(const Node* lhs, const Node* rhs)
	{
		return lhs->costSoFar > rhs->costSoFar;
	}
};