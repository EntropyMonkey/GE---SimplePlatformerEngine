#ifndef FLOOR_H
#define FLOOR_H

#include <glm/glm.hpp>
#include "SDL_image/SDL_image.h"

#include "Game.h"
#include "RectanglePO.h"
#include "GameObject.h"

#include "IMessageReceiver.h"
#include "Messenger.h"

namespace SPE
{
	class Game;

	public class Floor : public RectanglePO, public GameObject, public IMessageReceiver
	{
	public:
								Floor(Game *_game, Messenger *_messenger);

		void					Render();
		void					Update(float deltaTime);

		void					Receive(Message *message);
		void					Receive(CollisionMessage *message);

	private:
		Game*					game;

		GLuint					sprite;
		int						height;
	};
};

#endif
