#pragma once

#include "Error.hpp"

#include "GLSLProgram.h"
#include "InputManager.h"
#include "Console.h"
#include <glm/vec4.hpp>

namespace gines
{
	//Singletons
	extern InputManager inputManager;
	extern Console console;
	extern GLSLProgram colorProgram;

	//Global variables
	extern int consoleFontSize;
	extern int fpsCounterFontSize;
	extern glm::vec4 consoleTextColor;
	extern char* ginesFontPath;
	extern int consoleLines;

	////Main source file functions
	//Initialization
	bool initialize();
	void initializeShaders();
	int uninitialize();
	//Main loop
	void beginMainLoop();
	void endMainLoop();

}