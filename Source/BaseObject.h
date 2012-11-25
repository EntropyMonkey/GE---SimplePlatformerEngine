#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#define TAG_UNTAGGED -1

namespace SPE
{
	// all objects (i.e. PhysicsObjects and GameObjects) in the game are BaseObjects
	// the baseobject introduces an id for each object and also tags
	public class BaseObject
	{
	public:
		// starts at 1
		const unsigned int		id;
		const int				tag; // -1 >> not tagged

		BaseObject(int _tag = TAG_UNTAGGED) : 
			id(++nextFreeId),
			tag(_tag)
		{
		}

	private:
		static unsigned int		nextFreeId;
	};
};

#endif
