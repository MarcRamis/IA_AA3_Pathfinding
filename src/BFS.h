#pragma once
#include "Agent.h"
#include <queue>

class BFS : public Agent::PathFindingAlgorithm
{
private: 
	std::queue<Node*> frontier;

public:
	BFS();
	~BFS();
	virtual void CalculatePath(Agent* agent);
};