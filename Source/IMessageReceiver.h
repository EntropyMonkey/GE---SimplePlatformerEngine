#ifndef IMESSAGERECEIVER_H
#define IMESSAGERECEIVER_H

#include "Message.h"

#include "Messenger.h"

namespace SPE
{
	class Message;
	class Messenger;

	public class IMessageReceiver
	{
	public:
		IMessageReceiver(Messenger *messenger);

		virtual ~IMessageReceiver() {}

		virtual void Receive(Message *message) = 0;

	private:
		Messenger *messenger;
	};
};

#endif
