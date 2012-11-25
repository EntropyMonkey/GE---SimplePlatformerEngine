#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "BaseObject.h"

namespace SPE
{
	public class GameObject : public virtual BaseObject
	{
	public:
		bool					update;
		bool					render;

		virtual void 			Active(bool _update = true, bool _render = true)
		{
			update = _update;
			render = _render;
		}

		virtual void 			Update(float deltaTime) = 0;
		virtual void			Render() {};

	protected:
	};
};

#endif