#include "Messenger.h"

using namespace SPE;

Messenger::Messenger()
{
	receivers = new std::list<IMessageReceiver*>();
}

Messenger::~Messenger()
{
	delete receivers;
}

void Messenger::Register(IMessageReceiver *receiver)
{
	receivers->push_back(receiver);
}

void Messenger::SendMessage(Message &message)
{
	for (std::list<IMessageReceiver*>::iterator it = receivers->begin();
		it != receivers->end(); it++)
	{
		message.BeDelivered(*it);
	}
}
