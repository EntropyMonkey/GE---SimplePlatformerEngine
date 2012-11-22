#include "Background.h"

using namespace SPE;

Background::Background(Game *game)
{
	SpriteHelper::LoadTexture("Images/background.png", texture);

	position = vec2(0, 0);

	game->Add((GameObject*)this);
}

void Background::Render()
{
	glBindTexture(GL_TEXTURE_2D, texture);

	glPushMatrix();
	glTranslatef(position.x, position.y, 1);

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

void Background::Update(float deltaTime)
{

}