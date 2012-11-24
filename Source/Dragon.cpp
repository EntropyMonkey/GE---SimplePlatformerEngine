#include "Dragon.h"

using namespace SPE;
using namespace glm;

Dragon::Dragon(Game *game, Messenger *messenger) :
	IMessageReceiver(messenger)
{
	position = vec2(100, 200);
	size = vec2(220, 220);

	SpriteHelper::LoadTexture("Images/dragon_body.png", body);
	SpriteHelper::LoadTexture("Images/dragon_head.png", head);

	shootDirection = 0;
	turnSpeed = 15;
	turnClockwise = turnCounterClockwise = false;
	minAngle = -37;
	maxAngle = 28;

	game->Add((GameObject*)this);

	this->game = game;
}

Dragon::~Dragon()
{
	game->Remove((GameObject*) this);

	glDeleteTextures(1, &head);
	glDeleteTextures(1, &body);
}

void Dragon::Update(float deltaTime)
{
	if (turnClockwise)
	{
		shootDirection -= deltaTime * turnSpeed;
		shootDirection = (shootDirection < minAngle ? 
			minAngle : shootDirection);
	}

	if (turnCounterClockwise)
	{
		shootDirection += deltaTime * turnSpeed;
		shootDirection = (shootDirection > maxAngle ? 
			maxAngle : shootDirection);
	}
}

void Dragon::Render()
{
	glEnable(GL_BLEND);
	{
		ScopedMatrix m = ScopedMatrix();

		glTranslatef(position.x, position.y, 0);

		glBindTexture(GL_TEXTURE_2D, body);
		glBegin(GL_QUADS);
			// bottom left
			glTexCoord2f (0, 0);
			glVertex3f (0.0, 0.0, 0.0);

			// bottom right
			glTexCoord2f (1.0, 0.0);
			glVertex3f (size.x, 0.0, 0.0);

			// upper right
			glTexCoord2f (1.0, 1.0);
			glVertex3f (size.x, size.y, 0.0);
		
			// upper left
			glTexCoord2f (0.0, 1.0);
			glVertex3f (0.0, size.y, 0.0);
		glEnd();

		{
			ScopedMatrix m = ScopedMatrix();

			glTranslatef(size.x * 0.5f, size.y * 0.5f, 0);
			glRotatef(shootDirection, 0, 0, 1);
			glTranslatef(-size.x * 0.5f, -size.y * 0.5f, 0);

				glBindTexture(GL_TEXTURE_2D, head);

				glBegin(GL_QUADS);
					// bottom left
					glTexCoord2f (0, 0);
					glVertex3f (0.0, 0.0, 0.0);

					// bottom right
					glTexCoord2f (1.0, 0.0);
					glVertex3f (size.x, 0.0, 0.0);

					// upper right
					glTexCoord2f (1.0, 1.0);
					glVertex3f (size.x, size.y, 0.0);
		
					// upper left
					glTexCoord2f (0.0, 1.0);
					glVertex3f (0.0, size.y, 0.0);
				glEnd();
		}
	}

	glDisable(GL_BLEND);
}

void Dragon::Receive(Message *message)
{
	InputMessage *msg = dynamic_cast<InputMessage*>(message);
	if (msg)
		Receive(msg);
}

void Dragon::Receive(InputMessage *message)
{
	if (message->action == InputMessage::KEY_DOWN)
	{
		if (game->aiming)
		{
			if (message->key == SDLKey::SDLK_UP)
			{
				turnCounterClockwise = true;
				turnClockwise = false;
			}
			else if (message->key == SDLKey::SDLK_DOWN)
			{
				turnClockwise = true;
				turnCounterClockwise = false;
			}

			if (message->key == SDLKey::SDLK_SPACE)
			{
				game->Shoot(shootDirection);
			}
		}
	}
	else if (message->action == InputMessage::KEY_UP)
	{
		if (message->key == SDLKey::SDLK_UP)
		{
			turnCounterClockwise = false;
		}
		else if (message->key == SDLKey::SDLK_DOWN)
		{
			turnClockwise = false;
		}
	}
}
