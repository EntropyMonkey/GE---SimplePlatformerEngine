#ifndef SPRITEHELPER_H
#define SPRITEHELPER_H

#include "SDL.h"

namespace SPE
{
	public class SpriteHelper
	{
	public:
		static void GetRects(SDL_Rect *spriteRects, 
			unsigned int spriteNum, unsigned int spriteSize, 
			unsigned int spritesPerRow);
	};
};

#endif