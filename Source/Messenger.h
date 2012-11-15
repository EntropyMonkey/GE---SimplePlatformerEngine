#ifndef MESSENGER_H
#define MESSENGER_H

#include <list>

#include "Message.h"
#include "IMessageReceiver.h"

namespace SPE
{
	class IMessageReceiver;

	public class Messenger
	{
	public:
		Messenger();
		~Messenger();

		void							Register(IMessageReceiver *receiver);
		
		void							SendMessage(Message &message);

	private:
		std::list<IMessageReceiver*>*	receivers;
	};
};

#endif
