#include "Floor.h"

using namespace SPE;
using namespace glm;

Floor::Floor(Game *_game, Messenger *_messenger) :
	game(_game),
	IMessageReceiver(_messenger)
{
	game->Add((GameObject*) this);
	game->Add((PhysicsObject*) this);

	sprite = IMG_Load("Images/sprites/floor.png");

	height = 100;
	position = vec2(0, SCREEN_HEIGHT - height);
}

void Floor::Update(float deltaTime)
{

}

void Floor::Render()
{
	/*SDL_Rect r = SDL_Rect();
	r.x = position.x;
	r.y = position.y;
	r.w = SCREEN_WIDTH;
	r.h = height;
	SDL_BlitSurface(sprite, NULL, game->screen, &r);*/
}

void Floor::Receive(Message *message)
{
	{
		CollisionMessage *msg = dynamic_cast<CollisionMessage*>(message);
		if (msg)
		{
			Receive(msg);
		}
	}
}

void Floor::Receive(CollisionMessage *message)
{
	if (message->colliderOne == (PhysicsObject *)this ||
		message->colliderTwo == (PhysicsObject *)this)
	{
		printf("collision with floor!");
	}
}
