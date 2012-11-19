#ifndef SPRITEHELPER_H
#define SPRITEHELPER_H

#include <Windows.h>
#include <GL\GL.h>
#include <GL\glut.h>

#include <iostream>

#include "SDL.h"
#include "SDL_image/SDL_image.h"

#define X 0
#define Y 1
#define W 2
#define H 3

namespace SPE
{
	public class SpriteHelper
	{
	public:
		static void CalcTexCoords(float *spriteRects, 
			unsigned int spriteNum, unsigned int spriteSize,
			unsigned int spriteSheetSize,
			unsigned int spritesPerRow);

		static void LoadTexture(char *file, GLuint &texture);
	};
};

#endif