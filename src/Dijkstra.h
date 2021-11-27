#include "Agent.h"
#include <queue>
#include <stack>

class Dijkstra : public Agent::PathFindingAlgorithm
{
private:
	std::priority_queue<Node*, std::vector<Node*>, Node::CostSoFar> frontier;
	std::stack<Node*> path;
public:
	Dijkstra();
	~Dijkstra();
	virtual void CalculatePath(Agent* agent);
};


