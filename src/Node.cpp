#include "Node.h"

Node::Node()
{
}

Node::Node(Vector2D _pos, float _weight)
	: pos(_pos), weight(_weight)
{
}

Node::Node(Vector2D _pos, std::vector<Node*> _neighbours, float _weight) 
	: pos(_pos), neighbours(_neighbours), weight(_weight)
{
}

Node::~Node()
{
	for (int i = 0; i < (int)neighbours.size(); i++)
	{
		delete neighbours[i];
	}
}
