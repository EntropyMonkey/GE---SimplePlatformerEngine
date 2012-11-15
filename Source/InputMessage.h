#ifndef INPUTMESSAGE_H
#define INPUTMESSAGE_H

#include "SDL.h"

namespace SPE
{
	public class InputMessage : public Message
	{
	public:
		enum InputAction {KEY_DOWN, KEY_UP};

		InputMessage(InputAction _action, SDLKey _key):
			action(_action),
			key(_key)
		{

		}

		void BeDelivered(IMessageReceiver *receiver)
		{
			receiver->Receive(this);
		}

		InputAction	action;
		SDLKey key;
	};
};

#endif
