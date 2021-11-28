#include "SceneStrategy.h"

using namespace std;
const int MAX_PLAYERS = 2;

SceneStrategy::SceneStrategy()
{
	draw_grid = false;
	maze = new Grid("../res/maze.csv");

	loadTextures("../res/maze.png", "../res/coin.png");

	srand((unsigned int)time(NULL));

	Agent* soldier = new Agent;
	soldier->loadSpriteTexture("../res/soldier.png", 4);
	soldier->setGraph(maze);
	soldier->setBehavior(new PathFollowing);
	soldier->setPathfinder(new AStar);
	soldier->setTarget(Vector2D(-20, -20));
	agents.push_back(soldier);

	Agent* soldier2 = new Agent;
	soldier2->loadSpriteTexture("../res/soldier.png", 4);
	soldier2->setGraph(maze);
	soldier2->setBehavior(new PathFollowing);
	soldier2->setPathfinder(new AStar);
	soldier2->setTarget(Vector2D(-20, -20));
	agents.push_back(soldier2);

	/*Agent* zombie1 = new Agent;
	zombie1->loadSpriteTexture("../res/zombie1.png", 4);
	zombie1->setGraph(maze);
	zombie1->setBehavior(new PathFollowing);
	zombie1->setPathfinder(new AStar);
	zombie1->setTarget(Vector2D(-20, -20));
	agents.push_back(zombie1);*/

	/*Agent* zombie2 = new Agent;
	zombie2->loadSpriteTexture("../res/zombie2.png", 4);
	zombie2->setGraph(maze);
	zombie2->setBehavior(new PathFollowing);
	zombie2->setPathfinder(new AStar);
	zombie2->setTarget(Vector2D(-20, -20));
	agents.push_back(zombie2);*/

	// set agent position coords to the center of a random cell
	Vector2D rand_cell(-1, -1);

	for each (Agent * a in agents)
	{
		rand_cell = Vector2D(-1, -1);
		while (!maze->isValidCell(rand_cell))
			rand_cell = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
		a->setPosition(maze->cell2pix(rand_cell));
	}

	// set the coin in a random cell (but at least 3 cells far from the agent)
	coinPosition = Vector2D(-1, -1);
	while ((!maze->isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, rand_cell) < 3))
		coinPosition = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));

	for each (Agent * a in agents)
	{
		a->setGoal(maze->cell2pix(coinPosition));
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
}

void SceneStrategy::update(float dtime, SDL_Event* event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
			draw_grid = !draw_grid;

		if (event->key.keysym.scancode == SDL_SCANCODE_B) {
			for each (Agent* a in agents)
			{
				a->setPathfinder(new BFS);
			}
		}

		if (event->key.keysym.scancode == SDL_SCANCODE_D) {
			for each (Agent * a in agents)
			{
				a->setPathfinder(new Dijkstra);
			}
		}

		if (event->key.keysym.scancode == SDL_SCANCODE_G) {
			for each (Agent * a in agents)
			{
				a->setPathfinder(new Greedy);
			}
		}

		if (event->key.keysym.scancode == SDL_SCANCODE_A) {
			for each (Agent * a in agents)
			{
				a->setPathfinder(new AStar);
			}
		}

		break;
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			Vector2D cell = maze->pix2cell(Vector2D((float)(event->button.x), (float)(event->button.y)));
			if (maze->isValidCell(cell)) {
				agents[0]->addPathPoint(maze->cell2pix(cell));
			}
		}
		break;
	default:
		break;
	}

	for each (Agent * a in agents)
	{
		a->update(dtime, event);
	}

	// if we have arrived to the coin, replace it in a random cell!
	for each (Agent * a in agents)
	{
		if ((a->getCurrentTargetIndex() == -1) && (maze->pix2cell(a->getPosition()) == coinPosition))
		{
			coinPosition = Vector2D(-1, -1);
			while ((!maze->isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, maze->pix2cell(a->getPosition())) < 3))
				coinPosition = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));

			for each (Agent * a in agents)
			{
				a->setGoal(maze->cell2pix(coinPosition));
				a->clearPath();
				a->setNewPathSearch();
			}
		}
	}
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

	for each (Agent * a in agents)
	{
		a->draw();
	}
}

const char* SceneStrategy::getTitle()
{
	return "SDL Path Finding :: Strategy";
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
			else {
				// Do not draw if it is not necessary (bg is already black)
			}


		}
	}
	//Alternative: render a backgroud texture:
	//SDL_RenderCopy(TheApp::Instance()->getRenderer(), background_texture, NULL, NULL );
}

void SceneStrategy::drawCoin()
{
	Vector2D coin_coords = maze->cell2pix(coinPosition);
	int offset = CELL_SIZE / 2;
	SDL_Rect dstrect = { (int)coin_coords.x - offset, (int)coin_coords.y - offset, CELL_SIZE, CELL_SIZE };
	SDL_RenderCopy(TheApp::Instance()->getRenderer(), coin_texture, NULL, &dstrect);
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