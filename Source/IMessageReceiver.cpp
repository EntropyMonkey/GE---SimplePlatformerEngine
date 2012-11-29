#include "IMessageReceiver.h"

using namespace SPE;

IMessageReceiver::IMessageReceiver(Messenger *messenger, bool registerInstantly)
{
	if (registerInstantly)
		messenger->Register(this);

	this->messenger = messenger;
}

IMessageReceiver::~IMessageReceiver()
{
	if (messenger)
		messenger->UnRegister(this);
}