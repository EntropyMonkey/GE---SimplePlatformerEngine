#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

namespace SPE
{
	public class GameObject
	{
	public:
		bool					update;
		bool					render;

		void 					Active(bool _update = false, bool _render = false)
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