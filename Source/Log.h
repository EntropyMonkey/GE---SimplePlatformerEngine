#ifndef LOG_H
#define LOG_H

#include <iostream>

#include "IMessageReceiver.h"
#include "LogMessage.h"

namespace SPE
{
	public class Log : IMessageReceiver
	{
	public:
		Log (Messenger *_messenger);

		void Receive(Message *message);
		void Receive(LogMessage *message);
	};
};

#endif
