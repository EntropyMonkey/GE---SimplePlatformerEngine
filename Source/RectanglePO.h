#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <glm/glm.hpp>

//#include "Game.h"
#include "GameObject.h"
#include "PhysicsObject.h"

namespace SPE
{
	class Game;

	// a rectangular physics object
	public class RectanglePO : public PhysicsObject
	{
	public:
								RectanglePO(/*Game *_game*/);
		virtual void			Update(float deltaTime);

		virtual bool			TestCollision(PhysicsObject* other);

		virtual Shape			GetShape();

		void					SetSize(glm::vec2 _size);
		glm::vec2				GetSize();

	protected:
		glm::vec2				size;
	};
};

#endif