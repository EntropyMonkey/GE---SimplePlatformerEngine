#include "SpriteHelper.h"

using namespace SPE;

void SpriteHelper::CalcTexCoords(float* spriteRects, 
	unsigned int spriteNum, unsigned int spriteSize = 64, 
	unsigned int spriteSheetSize = 256, 
	unsigned int spritesPerRow = 3)
{
	float normalizedSpriteSize = (float)spriteSize / spriteSheetSize;
	int i = 0;
	for (int y = 0; y <= spriteNum / spritesPerRow; y++)
	{
		for (int x = 0; x < spritesPerRow; x++)
		{
			std::cout << std::endl << (spriteRects[i + X] = x * normalizedSpriteSize);
			std::cout << std::endl << (spriteRects[i + Y] = y * normalizedSpriteSize);
			std::cout << std::endl << (spriteRects[i + W] = spriteRects[i * 4 + X] + normalizedSpriteSize);
			std::cout << std::endl << (spriteRects[i + H] = spriteRects[i * 4 + Y] + normalizedSpriteSize);
			
			//printf("x: %f y: %f w: %f h: %f\n", spriteRects[i + X], spriteRects[i + Y], spriteRects[i + W], spriteRects[i + H]);
			i += 4;
		}
		std::cout << "--\n";
	}

	/*int x, y, i = 0;
	for (; y < spritesPerRow * spriteSize; y += spriteSize)
	{
		x = 0;
		for (; x < spritesPerRow * spriteSize; x += spriteSize, i++)
		{
			spriteRects[i * 4 + X] = (float)x / (float)spriteSheetSize;
			spriteRects[i * 4 + Y] = (float)y / (float)spriteSheetSize;
			spriteRects[i * 4 + W] = (float)x / spriteSheetSize + (float)spriteSize / (float)spriteSheetSize;
			spriteRects[i * 4 + H] = (float)y / spriteSheetSize + (float)spriteSize / (float)spriteSheetSize;

			printf("x: %f y: %f w: %f h: %f\n", spriteRects[i + X], spriteRects[i + Y], spriteRects[i + W], spriteRects[i + H]);

			if (i >= spriteNum)
				break;
		}

		if (i >= spriteNum)
			break;
	}*/
}

void SpriteHelper::LoadTexture(char *file, GLuint &texture)
{
	SDL_Surface *surface = IMG_Load(file);
	if (!surface)
	{
		printf("Could not load file at %s.\n", file);
		return;
	}

	// check image's width and height for power of two
	if ( (surface->w & (surface->w - 1)) != 0)
	{
		printf("LoadTexture: the image's width is not a power of two (%s)",
			file);
	}
	if ( (surface->h & (surface->h - 1)) != 0)
	{
		printf("LoadTexture: the image's height is not a power of two (%s)", 
			file);
	}
	
	// get color channels (alpha/not alpha)
	GLint nOfColors = surface->format->BytesPerPixel;
	GLenum textureFormat;
	if (nOfColors == 4)
    {
		textureFormat = GL_RGBA;
    } 
	else if (nOfColors == 3)
    {
        textureFormat = GL_RGB;
    } 
	else
	{
        printf("LoadTexture: the image (%s) is not true color..  this will probably break.\n", file);
    }

	// create gl texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0, 
		textureFormat, GL_UNSIGNED_BYTE, surface->pixels);

	SDL_FreeSurface(surface);
}
