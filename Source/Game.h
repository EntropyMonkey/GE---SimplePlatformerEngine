#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include <list>
#include "Time.h"

#include "GameObject.h"
#include "Physics.h"
#include "Player.h"

#define DEBUG_TIME TRUE

namespace SPE
{
	class Player;

	public class Game
	{
	public:
		SDL_Surface*			screen;

		Game();
		~Game();
		
		void					Add(GameObject *gameObject);
		void					Remove(GameObject *gameObject);

		void					SetTimeScale(float _timeScale);

		virtual void			Init();
		virtual void			Update(float deltaTime);
		virtual void			Render();

		void					UpdateGameObjects(float deltaTime);

		void					Quit();

	private:
		bool					quit;

		float					timeScale;
		float					deltaTime;
		float					lastUpdateTime;

		std::list<GameObject *> gameObjects;

		Physics*				physics;

		Player*					player;

		void					Play();
	};
};

#endif
