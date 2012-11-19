#include "IMessageReceiver.h"

using namespace SPE;

IMessageReceiver::IMessageReceiver(Messenger *messenger, bool registerInstantly)
{
	if (registerInstantly)
		messenger->Register(this);
}