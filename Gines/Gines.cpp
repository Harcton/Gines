#include "Gines.h"
#include "Time.h"
#include <SDL\SDL.h>
#include <GL/glew.h>
#include <iostream>

int WINDOW_WIDTH = 1280;
int WINDOW_HEIGHT = 720;
SDL_GLContext renderingContex;
SDL_Window *mWindow = nullptr;



namespace gines
{
	bool initialize()
	{
		SDL_Init(SDL_INIT_VIDEO);
		mWindow = SDL_CreateWindow("SDL project",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);

		if (mWindow == NULL)
		{
			std::cout << "\nInitialization failed! Failed to create window!";
			return false;
		}

		if ((renderingContex = SDL_GL_CreateContext(mWindow)) == NULL)
		{
			std::cout << "\nInitialization failed! Failed to create SDL rendering context!";
			return false;
		}

		if (glewInit() != GLEW_OK)
		{
			std::cout << "\nInitialization failed! Failed to initializez glew!";
			return false;
		}

		if (!gines::initializeTime())
		{
			std::cout << "\nInitialization failed! Failed to initialize time!";
			return false;
		}

		glClearColor(0.003f, 0.01f, 0.003f, 1.0f);
		std::cout << "\nPowered by... Gines (2015)";
		return true;
	}

	void uninitialize()
	{
		uninitializeTime();
	}





	void beginMainLoop()
	{
		beginFPS();
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void endMainLoop()
	{
		drawFPS();
		SDL_GL_SwapWindow(mWindow);
		endFPS();
	}
}