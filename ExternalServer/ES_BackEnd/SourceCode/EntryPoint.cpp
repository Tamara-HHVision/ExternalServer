#include <iostream>
#include "ServerInstance.h"


extern "C"
{
	__declspec(dllexport) int TestFunction()
	{
		//ES_BackEnd::ServerInstance::Logger();
		return 42;
	}
}