#include "SceneStrategy.h"
#include "Constants.h"

using namespace std;

SceneStrategy::SceneStrategy()
{
	draw_grid = false;
	maze = new Grid("../res/maze.csv");

	loadTextures("../res/maze.png", "../res/coin.png");

	srand((unsigned int)time(NULL));
	
	Agent* agent;

	agent = new Agent;
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agent->setGraph(maze);
	agent->setBehavior(new PathFollowing);
	agent->setPathfinder(new AStar);
	agent->setTarget(Vector2D(-20, -20));
	agents.push_back(agent);

	agent = new Agent;
	agent->loadSpriteTexture("../res/zombie2.png", 8);
	agent->setGraph(maze);
	agent->setBehavior(new PathFollowing);
	agent->setPathfinder(new AStar);
	agent->setTarget(Vector2D(-20, -20));
	agents.push_back(agent);

	Vector2D rand_cell;
	for (Agent* a : agents)
	{
		rand_cell = Vector2D(-1, -1);
		// set agent position coords to the center of a random cell
		while (!maze->isValidCell(rand_cell))
			rand_cell = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
		a->setPosition(maze->cell2pix(rand_cell));
	}

	// set the coin in a random cell (but at least 3 cells far from the agent)
	for (int i = 0; i < MAX_COINS; i++)
	{
		coins.push_back(new Vector2D(-1, -1));
		while ((!maze->isValidCell(*coins[i])) || (Vector2D::Distance(*coins[i], rand_cell) < 3))
			coins[i] = new Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
	}
	
	for (Agent *a : agents)
	{
		Vector2D coinPos = a->getNearestGoal(coins);
		a->setGoal(a->cell2pix(coinPos));
		a->setNewPathSearch();
		a->setOtherAgents(agents);
	}
}


SceneStrategy::~SceneStrategy()
{
	if (background_texture)
		SDL_DestroyTexture(background_texture);
	if (coin_texture)
		SDL_DestroyTexture(coin_texture);

	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}

	for (int i = 0; i < (int)coins.size(); i++)
	{
		delete coins[i];
	}
}

void SceneStrategy::update(float dtime, SDL_Event* event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
			draw_grid = !draw_grid;

		for (Agent* a : agents)
		{
			if (event->key.keysym.scancode == SDL_SCANCODE_B)
			{
				delete a->getPathfinder();
				a->clearPath();
				a->setPathfinder(new BFS);
				a->setNewPathSearch();
			}
			if (event->key.keysym.scancode == SDL_SCANCODE_D)
			{
				delete a->getPathfinder();
				a->clearPath();
				a->setPathfinder(new Dijkstra);
				a->setNewPathSearch();
			}
			if (event->key.keysym.scancode == SDL_SCANCODE_G)
			{
				delete a->getPathfinder();
				a->clearPath();
				a->setPathfinder(new Greedy);
				a->setNewPathSearch();
			}
			if (event->key.keysym.scancode == SDL_SCANCODE_A)
			{
				delete a->getPathfinder();
				a->clearPath();
				a->setPathfinder(new AStar);
				a->setNewPathSearch();
			}
		}
		break;
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			Vector2D cell = maze->pix2cell(Vector2D((float)(event->button.x), (float)(event->button.y)));
			for (Agent *a : agents)
			{
				if (maze->isValidCell(cell)) {
					a->addPathPoint(maze->cell2pix(cell));
				}
			}
		}
		break;
	default:
		break;
	}
	updateAgents(dtime,event);
}

void SceneStrategy::draw()
{
	drawMaze();
	drawCoin();

	if (draw_grid)
	{
		SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 255, 255, 127);
		for (int i = 0; i < SRC_WIDTH; i += CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), i, 0, i, SRC_HEIGHT);
		}
		for (int j = 0; j < SRC_HEIGHT; j = j += CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 0, j, SRC_WIDTH, j);
		}
	}

	for (Agent *a : agents)
	{
		a->draw();
	}
}

const char* SceneStrategy::getTitle()
{
	return "SDL Path Finding :: PathFinding Strategy";
}

void SceneStrategy::drawMaze()
{
	SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
	SDL_Rect rect;
	Vector2D coords;
	for (int j = 0; j < maze->getNumCellY(); j++)
	{
		for (int i = 0; i < maze->getNumCellX(); i++)
		{
			if (!maze->isValidCell(Vector2D((float)i, (float)j)))
			{
				SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
				coords = maze->cell2pix(Vector2D((float)i, (float)j)) - Vector2D((float)CELL_SIZE / 2, (float)CELL_SIZE / 2);
				rect = { (int)coords.x, (int)coords.y, CELL_SIZE, CELL_SIZE };
				SDL_RenderFillRect(TheApp::Instance()->getRenderer(), &rect);
			}
		}
	}
}

void SceneStrategy::drawCoin()
{
	for (Vector2D *coin : coins)
	{
		Vector2D coin_coords = maze->cell2pix(*coin);
		int offset = CELL_SIZE / 2;
		SDL_Rect dstrect = { (int)coin_coords.x - offset, (int)coin_coords.y - offset, CELL_SIZE, CELL_SIZE };
		SDL_RenderCopy(TheApp::Instance()->getRenderer(), coin_texture, NULL, &dstrect);
	}
}


bool SceneStrategy::loadTextures(char* filename_bg, char* filename_coin)
{
	SDL_Surface* image = IMG_Load(filename_bg);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	background_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	image = IMG_Load(filename_coin);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	coin_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	return true;
}

void SceneStrategy::updateAgents(float dtime, SDL_Event* event)
{
	avoidAgents();

	for (Agent* a : agents)
	{
		bool coinsExist = false;
		for (Vector2D* coin : coins)
		{
			// Test distance between agents & coins
			if ((Vector2D::Distance(maze->pix2cell(a->getPosition()), *coin) < 0.5f))
			{
				while ((!maze->isValidCell(*coin)) || (Vector2D::Distance(*coin, maze->pix2cell(a->getPosition())) < 3))
				{
					*coin = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
				}

				Vector2D coinPos = a->getNearestGoal(coins);
				a->setGoal(a->cell2pix(coinPos));
				a->clearPath();
				a->setNewPathSearch();
			}
			else if (maze->pix2cell(a->getGoal()) == *coin)
			{
				coinsExist = true;
			}
		}
		if (!coinsExist)
		{
			Vector2D coinPos = a->getNearestGoal(coins);
			a->setGoal(a->cell2pix(coinPos));
			a->clearPath();
			a->setNewPathSearch();
		}

		if (a->getVelocity().Length() < 1.0f)
		{
			Vector2D coinPos = a->getNearestGoal(coins);
			a->setGoal(a->cell2pix(coinPos));
			a->clearPath();
			a->setNewPathSearch();
		}
		a->update(dtime, event);
	}
}

void SceneStrategy::avoidAgents()
{
	for (Agent *a : agents)
	{
		for (Agent* a2 : agents)
		{
			if (a->getPosition() != a2->getPosition())
			{
				if ((Vector2D::Distance(maze->pix2cell(a->getPosition()), a2->pix2cell(a2->getPosition())) < MAX_AVOID_DISTANCE))
				{
					a->getGraph()->ChangeWeight(a2->pix2cell(a2->getPosition()));

					Vector2D coinPos = a->getNearestGoal(coins);
					a->setGoal(a->cell2pix(coinPos));
					a->clearPath();
					a->setNewPathSearch();
				}
				a->getGraph()->SetInitialWeight();
			}
		}
	}
}
