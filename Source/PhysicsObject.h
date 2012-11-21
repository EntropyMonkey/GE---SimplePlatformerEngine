#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include <iostream>
#include <glm/glm.hpp>

#include "Physics.h"

namespace SPE
{
	class Physics; // forward declaration

	public class PhysicsObject
	{
	public:
		enum Shape {RECTANGLE, CIRCLE};

		// starts at 1
		const unsigned int		id;
		
		bool					physicsActive;

		float					radius;

		float					mass;
		float					coeffOfRestitution;
		float					coeffOfFriction;

		glm::vec2				position;
		glm::vec2				velocity;
		glm::vec2				lastVelocity;
		glm::vec2				acceleration;

		//float					orientation; // current angle around the z-axis in degrees
		//float					angularVelocity;

		float					lastDeltaTime;

								PhysicsObject();
		virtual					~PhysicsObject();

		void 					Integrate(float deltaTime);

		virtual bool			TestCollision(PhysicsObject* other) = 0;
		void					Collide(PhysicsObject* other, glm::vec2 normal);

		// add an impulse force
		void					AddForce(glm::vec2 force);

		virtual Shape			GetShape() = 0;

	protected:
		bool					useGravity;
		glm::vec2				currentForce;
		PhysicsObject*			collisionObject;
		PhysicsObject*			lastCollisionObject;
			
	private:
		static unsigned int		nextFreeId;
	};
};

#endif