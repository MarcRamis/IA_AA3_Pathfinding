#pragma once
#include "Agent.h"
#include <queue>
#include <stack>

class Dijkstra : public Agent::PathFindingAlgorithm
{
private:
	//std::priority_queue<Node*, std::vector<Node*>, std::less<std::vector<Node*>::value_type>> frontier;
	std::priority_queue<Node*, std::vector<Node*>, Node> frontier;
	//std::priority_queue < Node*> frontier;
	float currentValue = 0;
	float costSoFar = 1000000;
	std::stack<Node*> path;
public:
	Dijkstra();
	~Dijkstra();
	virtual void CalculatePath(Agent* agent);

};


