#pragma once
#include "ScenePathFindingMouse.h"

class SceneStrategy :
	public Scene
{
public:
	SceneStrategy();
	~SceneStrategy();
	void update(float dtime, SDL_Event* event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	std::vector<Vector2D> coins;
	Vector2D coinPosition;

	Grid* maze;
	bool draw_grid;

	void drawMaze();
	void drawCoin();
	SDL_Texture* background_texture;
	SDL_Texture* coin_texture;
	bool loadTextures(char* filename_bg, char* filename_coin);

};
