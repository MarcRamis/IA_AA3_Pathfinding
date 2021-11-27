#include "Agent.h"
#include <queue>
#include <stack>

class Greedy : public Agent::PathFindingAlgorithm
{
private:
	std::priority_queue<Node*, std::vector<Node*>, Node::Heuristic> frontier;
	std::stack<Node*> path;
public:
	Greedy();
	~Greedy();
	virtual void CalculatePath(Agent* agent);
	float ManhattanDistance(Vector2D& n1, Vector2D& n2);
};