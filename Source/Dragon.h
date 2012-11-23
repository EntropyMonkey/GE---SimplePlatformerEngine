#ifndef DRAGON_H
#define DRAGON_H

#include <Windows.h>
#include <GL/GL.h>
#include <gl/glut.h>
#include <glm/glm.hpp>

#include "Game.h"
#include "GameObject.h"
#include "IMessageReceiver.h"
#include "InputMessage.h"

#include "ScopedMatrix.h"

namespace SPE
{
	class Game;

	public class Dragon : public GameObject, public IMessageReceiver
	{
	public:
		glm::vec2				position;
		glm::vec2				size;

								Dragon(Game *game, Messenger *messenger);
		virtual					~Dragon();

		void					Update(float deltaTime);
		void					Render();

		void					Receive(Message *message);
		void					Receive(InputMessage *message);

	private:
		Game *					game;

		float					shootDirection;
		GLuint					body;
		GLuint					head;

		bool					turnClockwise;
		bool					turnCounterClockwise;
		float					turnSpeed;

		float					maxAngle, minAngle;
	};
};

#endif
