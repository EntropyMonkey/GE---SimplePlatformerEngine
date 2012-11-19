#ifndef GAME_H
#define GAME_H

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_COLORDEPTH 32

#include <list>
#include <queue>
#include <Time.h>

#include <Windows.h>
#include "GL/GL.h"
#include "GL/glut.h"

#include <glm/glm.hpp>

#include "SDL.h"
#include "SDL_opengl.h"

#include "GameObject.h"
#include "Physics.h"
#include "Log.h"

#include "Player.h"
#include "Floor.h"

#include "IMessageReceiver.h"
#include "Messenger.h"
#include "Message.h"
#include "InputMessage.h"

namespace SPE
{
	class Player;
	class Floor;

	public class Game : public IMessageReceiver
	{
	public:
		SDL_Surface*			screen;

		Game();
		~Game();
		
		void					Add(PhysicsObject *physicsObject);
		void					Add(GameObject *gameObject);
		void					Remove(GameObject *gameObject);

		void					SetTimeScale(float _timeScale);

		virtual void			Init();
		virtual void			Update(float deltaTime);
		virtual void			Render();

		void					UpdateGameObjects(float deltaTime);

		void					Receive(Message *message);
		void					Receive(InputMessage *message);

		void					Reset();
		void					Quit();

	private:
		bool					quit;

		float					timeScale;
		float					deltaTime;
		float					lastUpdateTime;

		std::list<GameObject *> gameObjects;

		Log*					log;

		Messenger*				messenger;

		Physics*				physics;

		Player*					player1;
		Floor*					floor;

		void					Play();
	};
};

#endif
