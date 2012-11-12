#pragma  once

namespace SPE
{
	template <typename T>
	public class FSMState
	{
	public:
								FSMState(T *_owner)
								{
									owner = _owner;
								}

		virtual void			Enter() = 0;
		virtual void			Update(float deltaTime) = 0;
		virtual void			Exit() = 0;
		virtual void			HandleInput(char key, int keyState) = 0;

		char*					Name;

	protected:
		T*						owner;
	};
};