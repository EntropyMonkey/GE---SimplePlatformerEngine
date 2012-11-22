#include "Floor.h"

using namespace SPE;
using namespace glm;

Floor::Floor(Game *_game, Messenger *_messenger) :
	game(_game),
	IMessageReceiver(_messenger)
{
	game->Add((GameObject*) this);
	game->Add((PhysicsObject*) this);

	SpriteHelper::LoadTexture("Images/sprites/floor.png", sprite);

	position = vec2(0, 400);
	SetSize(vec2(100, 100));

	useGravity = false;
	mass = 0;
	textureOffset = 0;
	textureMovementSpeed = 0;
	coeffOfRestitution = 1.0f;
	coeffOfFriction = 500.0f; // it's a fake coefficient
}

Floor::~Floor()
{
	glDeleteTextures(1, &sprite);

	game->Remove((GameObject*)this);
	game->Remove((PhysicsObject*)this);
}

void Floor::Update(float deltaTime)
{
	textureOffset += deltaTime * 0.005f * textureMovementSpeed;
}

void Floor::Render()
{
	glBindTexture(GL_TEXTURE_2D, sprite);

	glPushMatrix();
	glTranslatef(position.x, position.y - size.y * 0.5, 0);

	int i = 6 * 4;
	float stretch = 100.0f;
	glBegin(GL_QUADS);
		// bottom left
		glTexCoord2f (0 + textureOffset, 0);
		glVertex3f (0.0, 0.0, 0.0);

		// bottom right
		glTexCoord2f (1.0 * stretch + textureOffset, 0.0);
		glVertex3f (size.x, 0.0, 0.0);

		// upper right
		glTexCoord2f (1.0 * stretch + textureOffset, 1.0);
		glVertex3f (size.x, size.y, 0.0);
		
		// upper left
		glTexCoord2f (0.0 + textureOffset, 1.0);
		glVertex3f (0.0, size.y, 0.0);
	glEnd();

	glPopMatrix();
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
		//printf("collision with floor!");
	}
}
