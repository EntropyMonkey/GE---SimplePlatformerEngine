#include "Game.h"

using namespace SPE;
using namespace std;

Game::Game()
{
    Init();

	quit = false;
	while (!quit)
	{
		Play();
	}

    SDL_Delay(3000);
}

// ------------------------------------------------------------- Initialize
void Game::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) 
	{
        printf("Can't init SDL:  %s\n", SDL_GetError());
        exit(1);
    }

    atexit(SDL_Quit);

    screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);

    if (screen == NULL) 
	{
        printf("Can't set video mode: %s\n", SDL_GetError());
        exit(1);
    }

	// initialize physics
	physics = new Physics();
	physics->Start();

	// initialize timescale
	timeScale = 1;

	// initialize player
	player = new Player(this);
}

// ------------------------------------------------------------- LOOP LOGIC
void Game::Play()
{
	int now = clock();
	deltaTime = (float)((now - lastUpdateTime) / CLOCKS_PER_SEC) / timeScale;
	lastUpdateTime = now;

	// call update method of the game
	Update(deltaTime);
	// call physics update
	physics->Update(deltaTime);
	// call update for each game object
	UpdateGameObjects(deltaTime);

	// render the game
	Render();
}

// ----------------------------------------------------------------- UPDATE
void Game::Update(float deltaTime)
{
#if DEBUG_TIME
	std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
	std::cout.precision(5);
	std::cout << deltaTime << std::endl;
#endif
	UpdateGameObjects(deltaTime);
}

void Game::UpdateGameObjects(float deltaTime)
{
	for (list<GameObject *>::iterator it = gameObjects.begin();
		it != gameObjects.end();
		it ++)
	{
		if ((*it)->update)
		{
			(*it)->Update(deltaTime);
		}
	}
}

// ----------------------------------------------------------------- RENDER
void Game::Render()
{
	player->Render();
	SDL_Flip(screen);
}

void Game::Quit()
{
	quit = true;

	delete player;
}

Game::~Game()
{
    SDL_Quit();
}

// ------------------------------------------------ GameObject registration
void Game::Add(GameObject *gameObject)
{
	gameObjects.push_back(gameObject);
}

void Game::Remove(GameObject *gameObject)
{
	gameObjects.remove(gameObject);
}