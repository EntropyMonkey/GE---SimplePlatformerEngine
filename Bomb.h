#ifndef BOMB_H
#define BOMB_H

#include "GameObject.h"
#include "PhysicsObject.h"
#include "IMessageReceiver.h"
#include "Message.h"

namespace SPE
{
	class Game;

	public class Bomb : 
		public GameObject, public CirclePO, public IMessageReceiver
	{
	public:
		Bomb(Game *game, Messenger *messenger);
		virtual ~Bomb();

		void					Render();
		void					Update(float deltaTime);

		void					Receive(Message *message);

		void					OnCollision(PhysicsObject *o1, PhysicsObject *o2) = 0;

	protected:
		Game *game;
		
		GLuint					sprites;
		float*					spriteRects;
		const unsigned int		spriteNum;
		const unsigned int		spriteSize;
	};
};

#endif
