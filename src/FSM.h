#ifndef FSM_H
#define FSM_H

#include "FSMState.h"

namespace SPE
{
	template <typename T>
	public class FSM
	{
	public:

								FSM(FSMState<T> *state)
								{
									lastState = NULL;
									currentState = state;
								}

		void					ChangeState(FSMState<T> *newState)
		{
			if (currentState != newState)
			{
				printf("Changed state %s to %s", currentState->Name, newState->Name);

				lastState = currentState;

				lastState->Exit();
			
				currentState = newState;
				currentState->Enter();
			}
		}

	protected:
		FSMState<T> *			lastState;
		FSMState<T> *			currentState;
	};
};

#endif