#include "Bomb.h"

using namespace SPE;
using namespace glm;

Bomb::Bomb(Game *game, Messenger *messenger, char* texturePath) :
	IMessageReceiver(messenger),
	spriteNum(7),
	spriteSize(64),
{
	this->game = game;
	game->Add((GameObject*)this);
	game->Add((PhysicsObject*)this);

	// load textures
	SpriteHelper::LoadTexture(texturePath, sprites);

	// set texture coords
	spriteRects = new float[spriteNum * 4]();

	float pixSize = 256.0f;
	int spritesPerRow = 3;
	vec2 size = vec2((float)spriteSize / pixSize, (float)spriteSize / pixSize);

	int x = 0; int y = 0;
	for (int i = 0; i < 7; i++)
	{
		spriteRects[i * 4 + X] = x * size.x;
		spriteRects[i * 4 + Y] = y * size.y;
		spriteRects[i * 4 + W] = spriteRects[i * 4 + X] + size.x;
		spriteRects[i * 4 + H] = spriteRects[i * 4 + Y] + size.y;

		x++;
		if (x >= spritesPerRow)
		{
			x = 0;
			y++;
		}
	}
}

Bomb::~Bomb()
{
	glDeleteTextures(1, sprites);
}