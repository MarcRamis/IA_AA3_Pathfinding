#include "Agent.h"

class AStar : public Agent::PathFindingAlgorithm
{
private:
	//std::priority_queue<Node*, std::vector<Node*>, Node> frontier;
	//std::stack<Node*> path;
public:
	AStar();
	~AStar();
	virtual void CalculatePath(Agent* agent);
};
