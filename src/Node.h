#pragma once
#include "Vector2D.h"

#include <vector>

class Node
{
private:

public:

	Vector2D pos;
	std::vector<Node*> neighbours;
	Node* comeFrom = nullptr;
	
	float weight = 0;
	float costSoFar = 0;
	float heuristic = 0;
	float priority = 0;


	Node();
	Node(Vector2D _pos, float _weight);
	Node(Vector2D _pos, std::vector<Node*> _neighbours, float _weight);
	~Node();
	
	struct CostSoFar
	{
		bool operator()(const Node* lhs, const Node* rhs)
		{
			return lhs->costSoFar > rhs->costSoFar;
		}
	};

	struct Heuristic
	{
		bool operator()(const Node* lhs, const Node* rhs)
		{
			return lhs->heuristic > rhs->heuristic;
		}
	};

	struct Priority
	{
		bool operator()(const Node* lhs, const Node* rhs)
		{
			return lhs->priority > rhs->priority;
		}
	};
};