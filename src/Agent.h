#pragma once
#include <iostream>
#include <minmax.h>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_SimpleApp.h"
#include "Path.h"
#include "Vector2D.h"
#include "utils.h"
#include "Graph.h"

class Agent
{
public:
	class SteeringBehavior
	{
	public:
		SteeringBehavior() {};
		virtual ~SteeringBehavior() {};
		virtual void applySteeringForce(Agent *agent, float dtime) {};
	};
	class PathFindingAlgorithm
	{
	protected:
		int countFrontier = 0;
		int counter = 0;

	public:
		PathFindingAlgorithm() {};
		virtual ~PathFindingAlgorithm() {};
		virtual void CalculatePath(Agent* agent) {};
	};
private:
	SteeringBehavior *steering_behaviour;
	Vector2D position;
	Vector2D velocity;
	Vector2D target;
	Vector2D goal;

	Path path;
	int currentTargetIndex;
	PathFindingAlgorithm *pathfinder;
	Graph *graph;

	float mass;
	float orientation;
	float max_force;
	float max_velocity;

	SDL_Texture *sprite_texture;
	bool draw_sprite;
	int sprite_num_frames;
	int sprite_w;
	int sprite_h;

	bool searchedPath;

public:
	Agent();
	~Agent();
	Vector2D getPosition();
	Vector2D getTarget();
	Vector2D getVelocity();
	float getMaxVelocity();
	float getMaxForce();
	float getMass();
	void setBehavior(SteeringBehavior* behavior);
	void setPathfinder(PathFindingAlgorithm *algorithm);
	void setPosition(Vector2D position);
	void setTarget(Vector2D target);
	void setVelocity(Vector2D velocity);
	void addPathPoint(Vector2D point);
	void setCurrentTargetIndex(int idx);
	int getCurrentTargetIndex();
	int getPathSize();
	Vector2D getPathPoint(int idx);
	void clearPath();
	void update(float dtime, SDL_Event *event);
	void draw();
	bool Agent::loadSpriteTexture(char* filename, int num_frames=1);
	void setGraph(Grid *grid);
	Graph* getGraph();
	Vector2D getNearestGoal(std::vector<Vector2D*> goals);
	Vector2D getGoal();
	void setGoal(Vector2D goal);
	void setNewPathSearch();
	PathFindingAlgorithm* getPathfinder();
			 
	Vector2D cell2pix(Vector2D cell);
	Vector2D pix2cell(Vector2D cell);
};