#include "SpriteHelper.h"

using namespace SPE;

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
