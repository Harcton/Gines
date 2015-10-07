#include <string>
#include <iostream>
#include <vector>

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Text.h"
#include "Gines.h"


int WINDOW_WIDTH = 1280;
int WINDOW_HEIGHT = 720;


//DEEBUGGIA...
void handleInput();
void increaseTextCount();
bool run = true;
std::vector<gines::Text*> texts;
//FPS:
void calculateFPS();
float time = 0;
float fps = 0;
float maxFPS = 60;
Uint32 deltaTime = 0;
//////////////



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





	/////////////////////////
	// Test area...
	glClearColor(0.003f, 0.01f, 0.003f, 1.0f);
	increaseTextCount();

	//Temp game loop
	while (run)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		Uint32 startTicks = SDL_GetTicks();
		time += deltaTime / 1000.0f;//TODO


		///////
		handleInput();
		for (unsigned i = 0; i < texts.size(); i++)
		{texts[i]->render();}
		SDL_GL_SwapWindow(mWindow);
		///////
		

		//FPS
		static int frameCounter = 0;
		frameCounter++;
		calculateFPS();
		if (frameCounter == 10)
		{
			std::cout << "\n" << fps;
			frameCounter = 0;
		}
		/////


		//Limit FPS
		Uint32 frameTicks = SDL_GetTicks() - startTicks;
		if (1000.0f / maxFPS > frameTicks)
			SDL_Delay(Uint32(1000.0f / maxFPS) - frameTicks);
		///////////
	}

	//Deallocate text memory...
	while (!texts.empty())
	{
		delete texts.back();
		texts.pop_back();
	}

	// End of test area....
	/////////////////////////


	std::cout << "\nExited succesfully";
	std::getchar();
	return 0;
}






//DEEBUGGIA...
void handleInput()
{
	float moveSpeed = texts.size();
	SDL_Event mEvent;
	while (SDL_PollEvent(&mEvent))
	{
		switch (mEvent.type)
		{
		case SDL_KEYDOWN:
			switch (mEvent.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				run = false;
				break;
			case SDLK_RETURN:
				increaseTextCount();
				std::cout << "\nText count increased! texts.size(): " << texts.size();
				break;
			case SDLK_UP:
				for (unsigned i = 0; i < texts.size(); i++)
				{texts[i]->translate(vec2f(0, float(moveSpeed * (float(i+1)/texts.size()))));}
				break;
			case SDLK_DOWN:
				for (unsigned i = 0; i < texts.size(); i++)
				{texts[i]->translate(vec2f(0, float(-moveSpeed * (float(i + 1) / texts.size()))));}
				break;
			case SDLK_LEFT:
				for (unsigned i = 0; i < texts.size(); i++)
				{texts[i]->translate(vec2f(float(-moveSpeed * (float(i + 1) / texts.size())), 0));}
				break;
			case SDLK_RIGHT:
				for (unsigned i = 0; i < texts.size(); i++)
				{texts[i]->translate(vec2f(float(moveSpeed * (float(i + 1) / texts.size())), 0));}
				break;
			}
			break;
		case SDL_QUIT:
			run = false;
			break;
		}
	}
}
void calculateFPS()
{
	static const int NUM_SAMPLES = 6;
	static Uint32 deltaTimes[NUM_SAMPLES];
	static int currentFrame = 0;

	static Uint32 previousTicks = SDL_GetTicks();

	Uint32 currentTicks;
	currentTicks = SDL_GetTicks();

	deltaTime = currentTicks - previousTicks;
	deltaTimes[currentFrame % NUM_SAMPLES] = deltaTime;

	previousTicks = currentTicks;

	int count;

	currentFrame++;
	if (currentFrame < NUM_SAMPLES)
		count = currentFrame;
	else
		count = NUM_SAMPLES;

	float deltaTimeAverage = 0;
	for (int i = 0; i < count; i++)
		deltaTimeAverage += deltaTimes[i];
	deltaTimeAverage /= count;

	if (deltaTimeAverage > 0)
		fps = 1000.0f / deltaTimeAverage;
	else
		fps = 0;
}
void increaseTextCount()
{
	char* fontPath = "Fonts/Ponderosa.ttf";
	if (texts.size() == 1)
		fontPath = "Fonts/Anonymous.ttf";
	else if (texts.size() == 2)
		fontPath = "Fonts/VeraMono.ttf";
	else if (texts.size() == 3)
		fontPath = "Fonts/DroidSansMono.ttf";
	

	texts.push_back(new gines::Text);
	if (texts.back()->setFont(fontPath, 18))
	{
		texts.back()->setFontSize(72);
		texts.back()->setPosition(vec2f(1, WINDOW_HEIGHT - 1 - texts.back()->getFontHeight()));
		texts.back()->setString("A very small string this is A very small string this is A very small string this is 100 glyphs total");
		//texts.back()->setString("Hey ma!I wanna be a rock star\nI told all my friends and bought myself a guitar\nWell the voice of disbelief was deafening\nThe look upon their faces, almost threatening\nAll that you could hear were cries of laughter\nSomeone even said I was a disaster, can you believe it ? (I can)\nHey ma!I wanna be a rock star\nI told all my friends and bought myself a guitar\nWell the voice of disbelief was deafening\nThe look upon their faces, almost threatening\nMaybe you'll be pleasantly surprised, you'd be right to trust me\nI believe the ghost of good news is gonna be haunting me\nWhy? I'll never know\nMaybe soon I'll find out\nI guess I'm in with a shout\nNever know if you don't try\nI don't know, I don't ask why\nThe voice of disbelief was deafening\nThe voice of disbelief was deafening\nHey ma!I wanna be a rock star\nHey ma why are you not listening?\nWhy are you not listening?\nThe voice of disbelief\nSaid the voice of disbelief\nHey ma!");
		texts.back()->setColor(vec4f(0.12f, 0.45f, 0.07f, 1.0f));
		texts.back()->render();//updates glyphs to render
	}

	int glyphsToRender = 0;
	for (unsigned i = 0; i < texts.size(); i++)
		glyphsToRender += texts[i]->glyphsToRender;
	std::cout << "\nGlyphs to render: " << glyphsToRender;
}
/////////////