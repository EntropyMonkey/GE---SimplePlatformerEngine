#include "Background.h"

using namespace SPE;
using namespace glm;

Background::Background(Game *game)
{
	SpriteHelper::LoadTexture("Images/background.png", texture);

	position = vec2(0, 0);
	size = vec2(1000, 1000);

	this->game = game;
	game->Add((GameObject*)this);
}

Background::~Background()
{
	game->Remove((GameObject*)this);

	glDeleteTextures(1, &texture);
}

void Background::Render()
{
	glBindTexture(GL_TEXTURE_2D, texture);

	{
		ScopedMatrix m = ScopedMatrix();
		glTranslatef(position.x, position.y, 1);

		glBegin(GL_QUADS);
			// bottom left
			glTexCoord2f (0, 0);
			glVertex3f (-size.x * 0.5f, -size.y * 0.5f, 0.0);

			// bottom right
			glTexCoord2f (1.0, 0.0);
			glVertex3f (size.x * 0.5f, -size.y * 0.5f, 0.0);

			// upper right
			glTexCoord2f (1.0, 1.0);
			glVertex3f (size.x * 0.5f, size.y * 0.5f, 0.0);
			
			// upper left
			glTexCoord2f (0.0, 1.0);
			glVertex3f (-size.x * 0.5f, size.y * 0.5f, 0.0);
		glEnd();
	}
}

void Background::Update(float deltaTime)
{
}