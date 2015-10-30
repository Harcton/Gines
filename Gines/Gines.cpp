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

		renderingContex = SDL_GL_CreateContext(mWindow);
		if (renderingContex == NULL)
		{
			std::cout << "\nInitialization failed! Failed to create SDL rendering context!";
			return false;
		}



		if (glewInit() != GLEW_OK)
		{
			std::cout << "\nInitialization failed! Failed to initializez glew!";
			return false;
		}


		glClearColor(0.003f, 0.01f, 0.003f, 1.0f);


		if (!gines::initializeTime())
		{
			std::cout << "\nInitialization failed! Failed to initialize time!";
			return false;
		}


		std::cout << "\nPowered by... Gines (2015)";
		return true;
	}

	void uninitialize()
	{


	}
}