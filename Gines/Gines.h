#ifndef GINES_H
#define GINES_H

#include "InputManager.h"
#include "Console.h"
#include <glm/vec4.hpp>

namespace gines
{
	//Singletons
	extern InputManager inputManager;
	extern Console console;

	//Global variables
	extern int consoleFontSize;
	extern int fpsCounterFontSize;
	extern glm::vec4 consoleTextColor;
	extern char* ginesFontPath;
	extern int consoleLines;

	////Main source file functions
	//Initialization
	bool initialize();
	int uninitialize();
	//Main loop
	void beginMainLoop();
	void endMainLoop();

}



#endif