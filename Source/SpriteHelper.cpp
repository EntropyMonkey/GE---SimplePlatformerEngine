#include "SpriteHelper.h"

using namespace SPE;

void SpriteHelper::GetRects(SDL_Rect *spriteRects, 
	unsigned int spriteNum, unsigned int spriteSize = 64, 
	unsigned int spritesPerRow = 3)
{
	int x, y, i = 0;
	for (; y < spritesPerRow * spriteSize; y += spriteSize)
	{
		x = 0;
		for (; x < spritesPerRow * spriteSize; x += spriteSize, i++)
		{
			spriteRects[i].x = x;
			spriteRects[i].y = y;
			spriteRects[i].w = spriteSize;
			spriteRects[i].h = spriteRects[i].w;

			if (i >= spriteNum)
				break;
		}

		if (i >= spriteNum)
			break;
	}
}