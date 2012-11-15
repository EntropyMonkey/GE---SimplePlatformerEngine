#include "IMessageReceiver.h"

using namespace SPE;

IMessageReceiver::IMessageReceiver(Messenger *messenger)
{
	messenger->Register(this);
}