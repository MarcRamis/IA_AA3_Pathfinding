#include "Agent.h"
#include <queue>
#include <stack>

class AStar : public Agent::PathFindingAlgorithm
{
private:
	std::priority_queue<Node*, std::vector<Node*>, Node::Priority> frontier;
	std::stack<Node*> path;
public:
	AStar();
	~AStar();
	virtual void CalculatePath(Agent* agent);

	float ManhattanDistance(Vector2D& n1, Vector2D& n2);
};
