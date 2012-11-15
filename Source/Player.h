#ifndef PLAYER_H
#define PLAYER_H

#include "SDL_image\SDL_image.h"

#include "Game.h"
#include "GameObject.h"
#include "PhysicsObject.h"
#include "SpriteHelper.h"
#include "IMessageReceiver.h"
#include "InputMessage.h"

namespace SPE
{
	class Game;

	public class Player : public GameObject, public IMessageReceiver
	{
	public:
		Player(Game *_game, Messenger *_messenger);
		~Player();

		void					Update(float deltaTime);
		void					Render();

		void					Receive(Message *message);
		void					Receive(InputMessage *message);

	private:
		Game*					game;

		SDL_Surface*			sprites;
		SDL_Rect*				spriteRects;
		const unsigned int		spriteNum;
	};
};

#endif
