#include "Gines.h"
#include "Time.h"

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <iostream>


int WINDOW_WIDTH = 1280;
int WINDOW_HEIGHT = 720;
SDL_GLContext renderingContex;
SDL_Window *mWindow = nullptr;


namespace gines
{
	//"Singleton" classes
	InputManager inputManager;
	Console console;
	GLSLProgram colorProgram;

	char* ginesFontPath = "Fonts/Anonymous.ttf";

	bool initialize()
	{
		Message("Initialize started...", gines::Message::Info);

		SDL_Init(SDL_INIT_VIDEO);
		mWindow = SDL_CreateWindow("SDL project",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);

		if (mWindow == NULL)
		{
			Message("Initialization failed! Failed to create window!", gines::Message::Fatal);
			return false;
		}

		if ((renderingContex = SDL_GL_CreateContext(mWindow)) == NULL)
		{
			Message("Initialization failed! Failed to create SDL rendering context!", gines::Message::Fatal);
			return false;
		}

		if (glewInit() != GLEW_OK)
		{
			Message("Initialization failed! Failed to initializez glew!", gines::Message::Fatal);
			return false;
		}

		if (!gines::initializeTime())
		{
			Message("Initialization failed! Failed to initialize time!", gines::Message::Fatal);
			return false;
		}

		if (console.initialize() != 0)
		{
			Message("Initialization failed! Failed to initialize console!", gines::Message::Fatal);
			return false;
		}
		
		initializeShaders(); 

		glClearColor(0.003f, 0.01f, 0.003f, 1.0f);
		Message("Initialized successfully!", gines::Message::Info);
		Message("Powered by... Gines(2015)", gines::Message::Info);
		return true;

	}

	void initializeShaders()
	{
		colorProgram.compileShaders("Shaders/color.vertex", "Shaders/color.fragment");
		colorProgram.addAttribute("vertexPosition");
		colorProgram.addAttribute("vertexColor");
		colorProgram.addAttribute("vertexUV");
		colorProgram.linkShaders();
	}

	int uninitialize()
	{
		uninitializeTime();
		console.unitialize();
		uninitializeTextRendering();

		Message("Exited succesfully", gines::Message::Info);
		std::getchar();
		return 0;
	}

	void beginMainLoop()
	{
		beginFPS();
		glClear(GL_COLOR_BUFFER_BIT);
		inputManager.update();
		console.update();
	}
	void endMainLoop()
	{
		console.render();
		drawFPS();
		SDL_GL_SwapWindow(mWindow);
		endFPS();
	}
}