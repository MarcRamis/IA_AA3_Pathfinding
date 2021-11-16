#pragma once
#include "Vector2D.h"

#include <vector>

class Node
{
public:

	Vector2D pos;
	std::vector<Node> *neighbours;
	float weight;

	Node();
	Node(Vector2D _pos, std::vector<Node> *_neighbours, float _weight);
};