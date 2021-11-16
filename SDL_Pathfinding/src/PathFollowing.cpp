#include "PathFollowing.h"

PathFollowing::PathFollowing()
{
}

PathFollowing::~PathFollowing()
{
}

void PathFollowing::applySteeringForce(Agent *agent, float dtime)
{
	//There is a path and we have not started to follow it
	if ((agent->getCurrentTargetIndex() == -1) && (agent->getPathSize()>0))
		agent->setCurrentTargetIndex(0);

	//We are in the middle of a path
	if (agent->getCurrentTargetIndex() >= 0)
	{
		float dist = Vector2D::Distance(agent->getPosition(), agent->getPathPoint(agent->getCurrentTargetIndex()));
		// We 've reached the current target
		if (dist < Path::ARRIVAL_DISTANCE)
		{
			// Current target is path's last point?
			if (agent->getCurrentTargetIndex() == agent->getPathSize() - 1)
			{
				if (dist < 3) // We've reached the end of the path
				{
					agent->clearPath();
					agent->setVelocity(Vector2D(0, 0));
					return;
				}
				else
				{
					// Arrive to current target
					float slow_factor = (agent->getTarget() - agent->getPosition()).Length() / Path::ARRIVAL_DISTANCE;

					Vector2D desired_velocity = agent->getTarget() - agent->getPosition();
					desired_velocity.Normalize();
					if ((agent->getTarget() - agent->getPosition()).Length() > Path::ARRIVAL_DISTANCE)
						desired_velocity *= agent->getMaxVelocity();
					else
						desired_velocity *= agent->getMaxVelocity() * slow_factor;

					Vector2D steering_force = desired_velocity - agent->getVelocity();
					steering_force /= agent->getMaxVelocity();
					steering_force = steering_force * agent->getMaxForce();

					Vector2D acceleration = steering_force / agent->getMass();
					agent->setVelocity(agent->getVelocity() + acceleration * dtime);
					agent->setVelocity(agent->getVelocity().Truncate(agent->getMaxVelocity()));

					agent->setPosition(agent->getPosition() + agent->getVelocity() * dtime);
					return;

				}
			}
			// Go to the next point in the path
			agent->setCurrentTargetIndex(agent->getCurrentTargetIndex() + 1);
		}
		// Seek to current target
		agent->setTarget(agent->getPathPoint(agent->getCurrentTargetIndex()));

		Vector2D desired_velocity = agent->getTarget() - agent->getPosition();
		desired_velocity.Normalize();
		desired_velocity *= agent->getMaxVelocity();

		Vector2D steering_force = desired_velocity - agent->getVelocity();
		steering_force /= agent->getMaxVelocity();
		steering_force = steering_force * agent->getMaxForce();

		Vector2D acceleration = steering_force / agent->getMass();
		agent->setVelocity(agent->getVelocity() + acceleration * dtime);
		agent->setVelocity(agent->getVelocity().Truncate(agent->getMaxVelocity()));

		agent->setPosition(agent->getPosition() + agent->getVelocity() * dtime);
		return;
	}
	// Do nothing if there is no path!
	return;
		
}
