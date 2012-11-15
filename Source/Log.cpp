#include "Log.h"

using namespace SPE;

Log::Log(Messenger *_messenger) :
	IMessageReceiver(_messenger)
{

}

void Log::Receive(Message *message)
{
	LogMessage * lm = dynamic_cast<LogMessage *>(message);
	if (lm)
		Receive(lm);
}

void Log::Receive(LogMessage *message)
{
	std::cout << message->text;
}
