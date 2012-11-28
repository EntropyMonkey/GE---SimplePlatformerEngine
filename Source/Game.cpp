#include "Game.h"

using namespace SPE;
using namespace std;
using namespace glm;

Game::Game() :
	spawnTime(5.0f)
{
	lastUpdateTime = clock();
    Init();

	quit = false;
	while (!quit)
	{
		Play();
	}
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

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 
		SCREEN_COLORDEPTH, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_OPENGL);
	
	// set gl matrices
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
 
	//glViewport(SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10);
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
 
	glClear(GL_COLOR_BUFFER_BIT);
 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
 
	glOrtho(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, -1.0f, 1.0f);
 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// initialize messenger
	messenger = new Messenger();

	// initialize log
	log = new Log(messenger);

	// initialize physics
	physics = new Physics(messenger);
	physics->Start();

	// initialize timescale
	timeScale = 1.0f;

	// initialize objects
	playerBomb = new Player(this, messenger);
	playerBomb->Active(false, false);
	floor = new LimitCollider(this, messenger);
	floor->position = vec2(0, 450);
	ceiling = new LimitCollider(this, messenger);
	ceiling->position = vec2(0, 0);

	dragon = new Dragon(this, messenger);
	background = new Background(this);
	spawnedBombs = new std::vector<Bomb*>();

	// initialize spawning
	spawnArea = vec2(100, 400);
	spawnHeadStart = 300;
	spawnTimer = spawnTime;

	srand(clock());

	aiming = true;
	startingGame = true;
	gameOver = false;

	startScreen = new InfoScreen("Images/startscreen.png");
	gameOverScreen = new InfoScreen("Images/gameoverscreen.png");
}

// ------------------------------------------------------------- LOOP LOGIC
void Game::Play()
{
	// events
	SDL_Event sdlEvent = SDL_Event();
	while (SDL_PollEvent(&sdlEvent))
	{
		// user closes window
		if (sdlEvent.type == SDL_QUIT)
		{
			quit = true;
			break;
		}
		else if (sdlEvent.type == SDL_KEYDOWN)
		{
			messenger->SendMessage(InputMessage(InputMessage::KEY_DOWN, sdlEvent.key.keysym.sym));
		}
		else if (sdlEvent.type == SDL_KEYUP)
		{
			messenger->SendMessage(InputMessage(InputMessage::KEY_UP, sdlEvent.key.keysym.sym));
		}
	}

	int now = clock();
	deltaTime = (float)((now - lastUpdateTime) / CLOCKS_PER_SEC) / timeScale;
	lastUpdateTime = now;

	// update
	Update(deltaTime);
	// physics update
	physics->Update(deltaTime);
	// call update for each game object
	UpdateGameObjects(deltaTime);

	// render the game
	Render();

	// remove game objects which have been marked for deletion
	for (list<GameObject*>::iterator it = gameObjectsToDelete.begin();
		it != gameObjectsToDelete.end();
		it++)
	{
		gameObjects.remove(*it);
	}

	gameObjectsToDelete.clear();
}

// ----------------------------------------------------------------- UPDATE
void Game::Update(float deltaTime)
{
	floor->textureMovementSpeed = playerBomb->velocity.x;
	floor->position.x = playerBomb->position.x;

	ceiling->textureMovementSpeed = floor->textureMovementSpeed;
	ceiling->position.x = floor->position.x;

	background->position.x = playerBomb->position.x;

	spawnTimer -= deltaTime;
	if (spawnTimer <= 0.0f)
	{
		spawnTimer = spawnTime;
		SpawnBomb();
		spawnTime *= 0.9f;
	}
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH);
	
	{
		ScopedMatrix m = ScopedMatrix();
		// this line's the camera
		cameraPos = playerBomb->position;
		cameraPos.x -= 200;
		cameraPos.y = 0;
		glTranslatef(-cameraPos.x, -cameraPos.y, 0);

		// render objects
		background->Render();
			
		floor->Render();
		ceiling->Render();
		dragon->Render();
	
		for (int i = 0; i < spawnedBombs->size(); i++)
		{
			if (spawnedBombs->operator [](i) != NULL)
				spawnedBombs->operator [](i)->Render();
		}

		playerBomb->Render();
	}
	
	if (startingGame)
	{
		startScreen->Render();
		SDL_GL_SwapBuffers();
		SDL_Delay(5000);
		startingGame = false;

		messenger->SendMessage(LogMessage("Game Started.\n"));
	}
	else if (gameOver)
	{
		gameOverScreen->Render();
		SDL_GL_SwapBuffers();
		messenger->SendMessage(LogMessage("Game Over.\n"));
		SDL_Delay(5000);
		Quit();
	}
	SDL_GL_SwapBuffers();
}

// ------------------------------------------------------------------ SHOOT
void Game::Shoot(float angle)
{
	aiming = false;

	playerBomb->position = vec2(
		dragon->position.x + dragon->size.x * 0.45f,
		dragon->position.y + dragon->size.x * 0.35f);
	playerBomb->velocity = vec2(0, 0);
	
	// take angle and shootspeed(radius of 1) as polar coordinates and convert them to
	// cartesian coords
	vec2 direction = vec2(cos(angle * DEG2RAD), sin(angle * DEG2RAD));

	playerBomb->Active(true, true);
	playerBomb->Shoot(direction);
}

// -------------------------------------------------------------- SPAWNBOMB
void Game::SpawnBomb()
{
	spawnedBombs->push_back(new Bomb(this, messenger));
	spawnedBombs->back()->position.x = playerBomb->position.x + spawnHeadStart;
	spawnedBombs->back()->position.y = (float)rand() / RAND_MAX * 
		(spawnArea.y - spawnArea.x) + spawnArea.x;
}

// ------------------------------------------------------------------ RESET
void Game::Reset()
{

}

// -------------------------------------------------------------- GAME OVER
void Game::GameOver()
{
	gameOver = true;
}

// ------------------------------------------------------------------- QUIT
void Game::Quit()
{
	quit = true;
}

Game::~Game()
{
	if (playerBomb)
		delete playerBomb;
	delete floor;
	delete ceiling;
	delete dragon;
	delete background;
	
	spawnedBombs->erase(spawnedBombs->begin(), spawnedBombs->end());
	delete spawnedBombs;
	
	delete messenger;
	delete physics;

    SDL_Quit();
}

// --------------------------------------------- PhysicsObject registration
void Game::Add(PhysicsObject *physicsObject)
{
	physics->Add(physicsObject);
}

void Game::Remove(PhysicsObject *physicsObject)
{
	physics->Remove(physicsObject);
}

// ------------------------------------------------ GameObject registration
void Game::Add(GameObject *gameObject)
{
	gameObjects.push_back(gameObject);
}

void Game::Remove(GameObject *gameObject)
{
	gameObjectsToDelete.push_back(gameObject); // make sure gameobjects are not deleted while updating them
}