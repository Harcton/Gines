#include <string>
#include <iostream>
#include <vector>

#include <SDL/SDL.h>
#include <glm/glm.hpp>

#include "Text.h"
#include "Gines.h"
#include "InputManager.h"
#include "Time.h"



// InputManager initialization.
InputManager inputManager;
//

//DEEBUGGIA...
void handleInput();
void increaseTextCount();
bool run = true;
std::vector<gines::Text*> texts;


extern SDL_Window *mWindow;
extern int WINDOW_HEIGHT;



int main(int argc, char** argv)
{
	if (!gines::initialize())
	{
		std::getchar();
		return false;
	}




	/////////////////////////
	// Test area...
	increaseTextCount();

	//Temp game loop
	while (run)
	{
		gines::beginMainLoop();


		//Event handling
		handleInput();


		//Rendering
		for (unsigned i = 0; i < texts.size(); i++)
		{texts[i]->render();}

		

		gines::endMainLoop();
	}

	//Deallocate text memory...
	while (!texts.empty())
	{
		delete texts.back();
		texts.pop_back();
	}

	// End of test area....
	/////////////////////////


	gines::uninitialize();
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
			inputManager.keyPress(mEvent.key.keysym.sym);
			break;

			// Useless, Teogod shalt smite this commented area once he graces us with his presence.

			/*
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
			*/

		case SDL_KEYUP:
			inputManager.keyRelease(mEvent.key.keysym.sym);
			break;

		case SDL_QUIT:
			run = false;
			break;
		}

		// These will likely be handled within the inputManager's handleInput function in the future. Will remain here for now.

		if (inputManager.isKeyPressed(SDLK_ESCAPE))
		{
			run = false;
		}
		if (inputManager.isKeyPressed(SDLK_RETURN))
		{
			increaseTextCount();
			std::cout << "\nText count increased! texts.size(): " << texts.size();
		}
		if (inputManager.isKeyPressed(SDLK_UP))
		{
			for (unsigned i = 0; i < texts.size(); i++)
			{
				texts[i]->translate(glm::vec2(0, float(moveSpeed * (float(i + 1) / texts.size()))));
			}
		}
		if (inputManager.isKeyPressed(SDLK_DOWN))
		{
			for (unsigned i = 0; i < texts.size(); i++)
			{
				texts[i]->translate(glm::vec2(0, float(-moveSpeed * (float(i + 1) / texts.size()))));
			}
		}
		if (inputManager.isKeyPressed(SDLK_LEFT))
		{
			for (unsigned i = 0; i < texts.size(); i++)
			{
				texts[i]->translate(glm::vec2(float(-moveSpeed * (float(i + 1) / texts.size())), 0));
			}
		}
		if (inputManager.isKeyPressed(SDLK_RIGHT))
		{
			for (unsigned i = 0; i < texts.size(); i++)
			{
				texts[i]->translate(glm::vec2(float(moveSpeed * (float(i + 1) / texts.size())), 0));
			}
		}
		
	}
}
void increaseTextCount()
{
	char* fontPath = "Fonts/Anonymous.ttf";
	if (texts.size() == 1)
		fontPath = "Fonts/Ponderosa.ttf";
	else if (texts.size() == 2)
		fontPath = "Fonts/VeraMono.ttf";
	else if (texts.size() == 3)
		fontPath = "Fonts/DroidSansMono.ttf";
	

	texts.push_back(new gines::Text);
	if (texts.back()->setFont(fontPath, 14))
	{
		//texts.back()->setFontSize(72);
		texts.back()->setPosition(glm::vec2(1, WINDOW_HEIGHT - 1 - texts.back()->getFontHeight()));
		//texts.back()->setString("A very small string this is A very small string \nthis is A very small string this is 100 glyphs total");
		texts.back()->setString("Hey ma!I wanna be a rock star\nI told all my friends and bought myself a guitar\nWell the voice of disbelief was deafening\nThe look upon their faces, almost threatening\nAll that you could hear were cries of laughter\nSomeone even said I was a disaster, can you believe it ? (I can)\nHey ma!I wanna be a rock star\nI told all my friends and bought myself a guitar\nWell the voice of disbelief was deafening\nThe look upon their faces, almost threatening\nMaybe you'll be pleasantly surprised, you'd be right to trust me\nI believe the ghost of good news is gonna be haunting me\nWhy? I'll never know\nMaybe soon I'll find out\nI guess I'm in with a shout\nNever know if you don't try\nI don't know, I don't ask why\nThe voice of disbelief was deafening\nThe voice of disbelief was deafening\nHey ma!I wanna be a rock star\nHey ma why are you not listening?\nWhy are you not listening?\nThe voice of disbelief\nSaid the voice of disbelief\nHey ma!");
		//texts.back()->setString("Black bird from evening sky\nRaven from heaths of night\nCome and take my cares\nCarry away the grief\nBereave me of my woes\nRend off these earthly throes\nFly them to deepest lakes\nTo the starlit shores");
		texts.back()->setColor(glm::vec4(0.12f, 0.45f, 0.07f, 1.0f));
		texts.back()->render();//updates glyphs to render
	}

	int glyphsToRender = 0;
	for (unsigned i = 0; i < texts.size(); i++)
		glyphsToRender += texts[i]->glyphsToRender;
	std::cout << "\nGlyphs to render: " << glyphsToRender;
}
/////////////