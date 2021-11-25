#pragma once
#include "Agent.h"
#include <queue>

class Dijkstra : public Agent::PathFindingAlgorithm
{
private:
	std::queue<Node*> frontier;

public:
	Dijkstra();
	~Dijkstra();
	virtual void CalculatePath(Agent* agent);

};

