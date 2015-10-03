#include <SDL/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <iostream>

#include "Text.h"

int WINDOW_WIDTH = 1280;
int WINDOW_HEIGHT = 720;


int main(int argc, char** argv)
{
	std::cout << "\nPowered by... Gines (2015)";
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *mWindow = SDL_CreateWindow("SDL project",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);

	if (mWindow == NULL)
	{
		return 1;
	}

	SDL_GLContext renderingContex = SDL_GL_CreateContext(mWindow);
	if (renderingContex == NULL)
	{
		return 1;
	}



	if (glewInit() != GLEW_OK)
	{
		return 1;
	}



	//run through the freetype test
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	{
		Text testText;
		if (testText.setFont("Fonts/Ponderosa.ttf", 14))
		{
			testText.setPosition(1, WINDOW_HEIGHT - 1 - testText.getFontHeight());
			testText.setString("Hey ma!I wanna be a rock star\nI told all my friends and bought myself a guitar\nWell the voice of disbelief was deafening\nThe look upon their faces, almost threatening\nAll that you could hear were cries of laughter\nSomeone even said I was a disaster, can you believe it ? (I can)\nHey ma!I wanna be a rock star\nI told all my friends and bought myself a guitar\nWell the voice of disbelief was deafening\nThe look upon their faces, almost threatening\nMaybe you'll be pleasantly surprised, you'd be right to trust me\nI believe the ghost of good news is gonna be haunting me\nWhy? I'll never know\nMaybe soon I'll find out\nI guess I'm in with a shout\nNever know if you don't try\nI don't know, I don't ask why\nThe voice of disbelief was deafening\nThe voice of disbelief was deafening\nHey ma!I wanna be a rock star\nHey ma why are you not listening?\nWhy are you not listening?\nThe voice of disbelief\nSaid the voice of disbelief\nHey ma!");
			testText.setColor(0.12f, 0.45f, 0.07f, 1.0f);
			testText.render();
		}
	}

	SDL_GL_SwapWindow(mWindow);


	std::cout << "\nExited succesfully";
	std::getchar();
	return 0;
}