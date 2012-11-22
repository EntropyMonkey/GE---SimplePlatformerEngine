#include "Game.h"

using namespace SPE;
using namespace std;
using namespace glm;

Game::Game() :
	IMessageReceiver(messenger, false)
{
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
	messenger->Register(this);

	// initialize log
	log = new Log(messenger);

	// initialize physics
	physics = new Physics(messenger);
	physics->Start();

	// initialize timescale
	timeScale = 1;

	// initialize objects
	currentBomb = new Player(this, messenger);
	currentBomb->Active(false, false);
	
	floor = new Floor(this, messenger);

	dragon = new Dragon(this, messenger);

	aiming = true;

	messenger->SendMessage(LogMessage("Game Started.\n"));
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
}

// ------------------------------------------------------- Receive Messages
void Game::Receive(Message *message)
{
	InputMessage *msg = dynamic_cast<InputMessage*>(message);
	if (msg)
		Receive(msg);
}

void Game::Receive(InputMessage *message)
{
	if (message->action == InputMessage::KEY_UP)
	{
		if (message->key == SDLKey::SDLK_SPACE)
		{
			Reset();
			SDL_GL_SwapBuffers();
		}
	}
}

// ----------------------------------------------------------------- UPDATE
void Game::Update(float deltaTime)
{
	floor->textureMovementSpeed = currentBomb->velocity.x;
	floor->position.x = currentBomb->position.x;

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH);

	glPushMatrix();
	// this line's the camera
	glTranslatef(-(currentBomb->position.x - /*currentBomb->radius -*/ 200), 0, 0);
		// render objects
		floor->Render();
		dragon->Render();
	
		currentBomb->Render();
	glPopMatrix();

	SDL_GL_SwapBuffers();
}

// ------------------------------------------------------------------ SHOOT
void Game::Shoot(float angle)
{
	aiming = false;

	currentBomb->position = vec2(
		dragon->position.x + dragon->size.x * 0.45f,
		dragon->position.y + dragon->size.x * 0.35f);
	currentBomb->velocity = vec2(0, 0);
	
	// take angle and shootspeed(radius of 1) as polar coordinates and convert them to
	// cartesian coords
	vec2 direction = vec2(cos(angle * DEG2RAD), sin(angle * DEG2RAD));

	currentBomb->Active(true, true);
	currentBomb->Shoot(direction);
}

// ------------------------------------------------------------------ RESET
void Game::Reset()
{
}

// ------------------------------------------------------------------- QUIT
void Game::Quit()
{
	quit = true;
}

Game::~Game()
{
	if (currentBomb)
		delete currentBomb;
	delete floor;
	delete dragon;
	
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
	gameObjects.remove(gameObject);
}