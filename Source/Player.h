#ifndef PLAYER_H
#define PLAYER_H

#include "SDL.h"
#include "SDL_image\SDL_image.h"

#include "Game.h"
#include "GameObject.h"
#include "CirclePO.h"
#include "SpriteHelper.h"

#include "IMessageReceiver.h"
#include "InputMessage.h"
#include "CollisionMessage.h"

namespace SPE
{
	class Game;

	public class Player : public GameObject, public CirclePO, public IMessageReceiver
	{
	public:
		Player(Game *_game, Messenger *_messenger);
		~Player();

		void					Update(float deltaTime);
		void					Render();

		void					Receive(Message *message);
		void					Receive(InputMessage *message);
		void					Receive(CollisionMessage *message);

	private:
		Game*					game;

		GLuint					sprites;
		float*					spriteRects;
		const unsigned int		spriteNum;
		const unsigned int		spriteSize;
	};
};

#endif
