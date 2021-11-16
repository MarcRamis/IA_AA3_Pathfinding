#include "Node.h"

Node::Node()
{
}

Node::Node(Vector2D _pos, std::vector<Node>* _neighbours, float _weight) 
	: pos(_pos), neighbours(_neighbours), weight(_weight)
{
}
