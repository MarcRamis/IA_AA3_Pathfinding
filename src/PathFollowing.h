#pragma once
#include "Agent.h"
#include "Vector2D.h"

class PathFollowing :
	public Agent::SteeringBehavior
{
public:
	PathFollowing();
	~PathFollowing();
	void applySteeringForce(Agent *agent, float dtime);
};
