#ifndef MESSAGE_H
#define MESSAGE_H

#include "IMessageReceiver.h"

namespace SPE
{
	class IMessageReceiver;
	class Messenger;

	public class Message
	{
	public:
		virtual ~Message() { }

		virtual void BeDelivered(IMessageReceiver *receiver) = 0;

	protected:
	};
};

#endif
