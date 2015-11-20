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
		Log::Message("Initialize started...", Log::Level::Info);

		SDL_Init(SDL_INIT_VIDEO);
		mWindow = SDL_CreateWindow("SDL project",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);

		if (mWindow == NULL)
		{
			Log::Message("Initialization failed! Failed to create window!", Log::Level::Fatal);
			return false;
		}

		if ((renderingContex = SDL_GL_CreateContext(mWindow)) == NULL)
		{
			Log::Message("Initialization failed! Failed to create SDL rendering context!", Log::Level::Fatal);
			return false;
		}

		if (glewInit() != GLEW_OK)
		{
			Log::Message("Initialization failed! Failed to initializez glew!", Log::Level::Fatal);
			return false;
		}

		if (!gines::initializeTime())
		{
			Log::Message("Initialization failed! Failed to initialize time!", Log::Level::Fatal);
			return false;
		}

		if (console.initialize() != 0)
		{
			Log::Message("Initialization failed! Failed to initialize console!", Log::Level::Fatal);
			return false;
		}

		// WIP, error c5060
		
		 initializeShaders(); 

		glClearColor(0.003f, 0.01f, 0.003f, 1.0f);
		Log::Message("Initialized successfully!", Log::Level::Info);
		Log::Message("Powered by... Gines(2015)", Log::Level::Info);
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

		std::cout << "\nExited succesfully";
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