#include "Game.h"

using namespace SPE;
using namespace std;

Game::Game() :
	IMessageReceiver(messenger, false)
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

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 
		SCREEN_COLORDEPTH, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_OPENGL);

    if (screen == NULL) 
	{
        printf("Can't set video mode: %s\n", SDL_GetError());
        exit(1);
    }
	
	// set gl matrices
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
 
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
	player1 = new Player(this, messenger);

	floor = new Floor(this, messenger);

	messenger->SendMessage(LogMessage("Game Started.\n"));
}

// ------------------------------------------------------------- LOOP LOGIC
void Game::Play()
{
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

	// call update method of the game
	Update(deltaTime);
	// call physics update
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

	// render objects
	floor->Render();
	player1->Render();

	SDL_GL_SwapBuffers();
	//SDL_Flip(screen);
}

// ------------------------------------------------------------------ RESET
void Game::Reset()
{
	player1->position = glm::vec2(300, 0);
}

// ------------------------------------------------------------------- QUIT
void Game::Quit()
{
	quit = true;
}

Game::~Game()
{
	delete messenger;
	delete physics;
	delete player1;
	delete floor;

    SDL_Quit();
}

// --------------------------------------------- PhysicsObject registration
void Game::Add(PhysicsObject *physicsObject)
{
	physics->Add(physicsObject);
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