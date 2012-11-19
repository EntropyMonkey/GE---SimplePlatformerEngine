#include "Physics.h"

using namespace SPE;
using namespace std;

Physics::Physics(Messenger *_messenger) :
	messenger(_messenger)
{
	physicsObjects = new set<PhysicsObject*>();
	started = false;
}

Physics::~Physics()
{
	// do not delete single physics objects here because the game objects
	// will be deleted in the game
	delete physicsObjects;
}

void Physics::Start()
{
	started = true;
}

void Physics::Add(PhysicsObject *object)
{
	physicsObjects->insert(object);
}

void Physics::Remove(PhysicsObject *object)
{
	physicsObjects->erase(object);
}

void Physics::Update(float deltaTime)
{
	if (!started || physicsObjects->empty())
		return;

	// filter collisions based on the collision matrix:
	//    | o1 | o2 | o3 | o4 | ...
	// o1 |    | x  | x  |  x | ...
	// o2 |    |    | x  |  x | ...
	// o3 |    |    |    |  x | ...
	// .. |    |    |    |  ..| ...
	// 
	// the x marks which two objects collide
	set<PhysicsObject*>::iterator it1, it2;
	it1 = physicsObjects->begin();
	int i, j;
	const int numPhysicsObjects = physicsObjects->size();

	for (i = 0; i < numPhysicsObjects; i++)
	{
		it2 = physicsObjects->begin();
		// do not collide objects below the matrix diagonal
		for (j = 0; j <= i; j++)
		{
			it2++;
		}
		// collide objects above the matrix's diagonal
		for (; j < numPhysicsObjects; j++)
		{
			if ((*it1)->TestCollision(*it2))
			{
				messenger->SendMessage(CollisionMessage(*it1, *it2));
			}
			it2++;
		}

		// update the physics of this object
		(*it1)->Integrate(deltaTime);

		it1++;
	}
}