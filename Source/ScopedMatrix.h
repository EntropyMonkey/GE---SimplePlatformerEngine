#ifndef SCOPEDMATRIX_H
#define SCOPEDMATRIX_H

#include <Windows.h>
#include <GL/GL.h>
#include <GL/glut.h>

namespace SPE
{
	// automatically pops matrix when leaving scope
	public class ScopedMatrix
	{
	public:
		ScopedMatrix()
		{
			glPushMatrix();
		}

		~ScopedMatrix()
		{
			glPopMatrix();
		}
	};
};

#endif
