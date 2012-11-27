#ifndef BOMB_H
#define BOMB_H

#include "Game.h"
#include "GameObject.h"
#include "CirclePO.h"

#include "IMessageReceiver.h"
#include "Message.h"
#include "CollisionMessage.h"

#include "ScopedMatrix.h"

namespace SPE
{
	class Game;

	public class Bomb : 
		public GameObject, public CirclePO, public IMessageReceiver
	{
	public:
		Bomb(Game *game, Messenger *messenger, char* texturePath = "Images/Sprites/bomb.png");
		virtual ~Bomb();

		virtual void			Render();
		virtual void			Update(float deltaTime);

		virtual void			Receive(Message *message);
		void					Receive(CollisionMessage *message);

		void					OnCollision(PhysicsObject *o1, PhysicsObject *o2);

		void					ChangeSpriteFrame();

	protected:
		Game *					game;
		
		GLuint					sprites;
		float*					spriteRects;
		const unsigned int		spriteNum;
		const unsigned int		spriteSize;
		int						currentSprite;
		bool					enteredScreen;
		float					liveTime;
	};
};

#endif
