#ifndef INFOSCREEN_H
#define INFOSCREEN_H

#include <Windows.h>
#include <GL/GL.h>
#include <GL/glut.h>

#include "SpriteHelper.h"

namespace SPE
{
	public class InfoScreen
	{
	public:
		InfoScreen(char *file)
		{
			SpriteHelper::LoadTexture(file, texture);
		}

		~InfoScreen()
		{
			glDeleteTextures(1, &texture);
		}

		void Render()
		{
			glBindTexture(GL_TEXTURE_2D, texture);

			glBegin(GL_QUADS);
				// bottom left
				glTexCoord2f (0, 0);
				glVertex3f (0.0, 0.0, 0.0);

				// bottom right
				glTexCoord2f (1, 0);
				glVertex3f (SCREEN_WIDTH, 0.0, 0.0);

				// upper right
				glTexCoord2f (1, 1);
				glVertex3f (SCREEN_WIDTH, SCREEN_HEIGHT, 0.0);
		
				// upper left
				glTexCoord2f (0, 1);
				glVertex3f (0.0, SCREEN_HEIGHT, 0.0);
			glEnd();
		}

	protected:
		GLuint texture;
	};
};

#endif
