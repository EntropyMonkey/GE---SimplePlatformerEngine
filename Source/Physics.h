#ifndef PHYSICS_H
#define PHYSICS_H

#include <set>

#include "PhysicsObject.h"

namespace SPE
{
	class PhysicsObject; // forward declaration

	const float GRAVITY = -9.81f;

	public class Physics
	{
	public:
								Physics();
								~Physics();

		void					Add(PhysicsObject *object);
		void					Remove(PhysicsObject *object);

		void					Update(float deltaTime);

		void					Start();
		

	protected:
		std::set<PhysicsObject *> *physicsObjects;
		bool					started;
	};
};

#endif