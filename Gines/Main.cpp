#include <SDL/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>




int main(int argc, char** argv)
{
	std::cout << "\nPowered by... Gines (2015)";
	SDL_Init(SDL_INIT_VIDEO);
	
	SDL_Window *mWindow = SDL_CreateWindow("SDL project",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		600, 400, SDL_WINDOW_OPENGL);

	if (mWindow == NULL)
	{return 1;}

	SDL_GLContext renderingContex = SDL_GL_CreateContext(mWindow);
	if (renderingContex == NULL)
	{return 1;}

	if (glewInit() != GLEW_OK)
	{return 1;}

	std::cout << "\nExited succesfully";
	std::getchar();
	return 0;
}