#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <Windows.h>
#include <GL/GL.h>
#include <GL/glut.h>

#include <glm/glm.hpp>

#include "Game.h"
#include "GameObject.h"

namespace SPE
{
	class Game;

	public class Background : public GameObject
	{
	public:
		vec2 position;
		Background(Game *game);

		void Render();
		void Update(float deltaTime);

	private:
		GLuint texture;
	};
};

#endif
