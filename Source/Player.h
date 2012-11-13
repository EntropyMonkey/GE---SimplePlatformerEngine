#ifndef PLAYER_H
#define PLAYER_H

#include "Game.h"
#include "GameObject.h"

namespace SPE
{
	class Game;

	public class Player : GameObject
	{
	public:
		Player(Game *_game);
		~Player();

		void					Update(float deltaTime);
		void					Render();

	private:
		Game*					game;

		SDL_Surface*			image;
	};
};

#endif
