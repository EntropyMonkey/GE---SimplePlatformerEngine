#ifndef LOGMESSAGE_H
#define LOGMESSAGE_H

#include "Message.h"

namespace SPE
{
	public class LogMessage : public Message
	{
	public:
		LogMessage(char *_text)
		{
			text = _text;
		}

		void BeDelivered(IMessageReceiver *receiver)
		{
			receiver->Receive(this);
		}

		char* text;
	};
};

#endif
