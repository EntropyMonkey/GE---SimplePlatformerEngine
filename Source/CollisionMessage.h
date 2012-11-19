#ifndef COLLISIONMESSAGE_H
#define COLLISIONMESSAGE_H

#include <glm/glm.hpp>

#include "PhysicsObject.h"
#include "Message.h"

namespace SPE
{
	class PhysicsObject;

	public class CollisionMessage : public Message
	{
	public:
		CollisionMessage(PhysicsObject *one, PhysicsObject *two) :
			colliderOne(one), colliderTwo(two)
		{
		}

		void BeDelivered(IMessageReceiver *receiver)
		{
			receiver->Receive(this);
		}

		PhysicsObject *colliderOne;
		PhysicsObject *colliderTwo;
	};
};

#endif
