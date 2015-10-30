#ifndef GINES_H
#define GINES_H

#include "InputManager.h"
#include "Console.h"


namespace gines
{
	//Singletons
	extern InputManager inputManager;
	extern Console console;

	bool initialize();
	int uninitialize();

	void beginMainLoop();
	void endMainLoop();

}



#endif