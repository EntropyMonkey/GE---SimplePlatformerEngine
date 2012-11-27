#include "LimitCollider.h"

using namespace SPE;
using namespace glm;

LimitCollider::LimitCollider(Game *_game, Messenger *_messenger) :
	game(_game),
	IMessageReceiver(_messenger)
{
	game->Add((GameObject*) this);
	game->Add((PhysicsObject*) this);

	SpriteHelper::LoadTexture("Images/sprites/floor.png", sprite);

	SetSize(vec2(10000, 100));

	useGravity = false;
	mass = 0;
	textureOffset = 0;
	textureMovementSpeed = 0;
	coeffOfRestitution = 0.8f;
	coeffOfFriction = 500.0f; // it's a fake coefficient
}

LimitCollider::~LimitCollider()
{
	game->Remove((GameObject*)this);
	game->Remove((PhysicsObject*)this);

	glDeleteTextures(1, &sprite);
}

void LimitCollider::Update(float deltaTime)
{
	textureOffset += deltaTime * 0.005f * textureMovementSpeed;
}

void LimitCollider::Render()
{
	glBindTexture(GL_TEXTURE_2D, sprite);

	{
		ScopedMatrix m = ScopedMatrix();

		glTranslatef(position.x, position.y, 0);

		int i = 6 * 4;
		float stretch = 100.0f;
		glBegin(GL_QUADS);
			// bottom left
			glTexCoord2f (0 + textureOffset, 0);
			glVertex3f (-size.x * 0.5f, -size.y * 0.5f, 0.0);

			// bottom right
			glTexCoord2f (1.0 * stretch + textureOffset, 0.0);
			glVertex3f (size.x * 0.5f, -size.y * 0.5f, 0.0);

			// upper right
			glTexCoord2f (1.0 * stretch + textureOffset, 1.0);
			glVertex3f (size.x * 0.5f, size.y * 0.5f, 0.0);
		
			// upper left
			glTexCoord2f (0.0 + textureOffset, 1.0);
			glVertex3f (-size.x * 0.5f, size.y * 0.5f, 0.0);
		glEnd();
	}
}

void LimitCollider::Receive(Message *message)
{
	{
		CollisionMessage *msg = dynamic_cast<CollisionMessage*>(message);
		if (msg)
		{
			Receive(msg);
		}
	}
}

void LimitCollider::Receive(CollisionMessage *message)
{
	if (message->colliderOne == (PhysicsObject *)this ||
		message->colliderTwo == (PhysicsObject *)this)
	{
	}
}
