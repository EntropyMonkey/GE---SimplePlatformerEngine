#ifndef FLOOR_H
#define FLOOR_H

#include <glm/glm.hpp>
#include "SDL_image/SDL_image.h"

#include "Game.h"
#include "RectanglePO.h"
#include "GameObject.h"

#include "IMessageReceiver.h"
#include "Messenger.h"

#include "ScopedMatrix.h"

namespace SPE
{
	class Game;

	public class Floor : public RectanglePO, public GameObject, public IMessageReceiver
	{
	public:
		float					textureMovementSpeed;

								Floor(Game *_game, Messenger *_messenger);
		virtual					~Floor();

		void					Render();
		void					Update(float deltaTime);

		void					Receive(Message *message);
		void					Receive(CollisionMessage *message);

	private:
		Game*					game;

		GLuint					sprite;
		float					textureOffset; // used for emulating movement
	};
};

#endif
