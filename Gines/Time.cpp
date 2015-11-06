#include <SDL\SDL_timer.h>
#include <iostream>

#include "Time.h"
#include "Text.h"

#define FPS_REFRESH_RATE 5

extern int WINDOW_HEIGHT;

namespace gines
{
	//Global variables
	extern char* ginesFontPath;
	int fpsCounterFontSize = 40;
	bool showFps = true;


	//Local variables
	float fps = 0;
	float maxFPS = 60;
	Uint32 deltaTime = 0;
	float runTime = 0;
	Uint32 startTicks = 0;
	gines::Text* fpsCounter;
	static bool initialized = false;
	static int previousFontSize = fpsCounterFontSize;



	bool initializeTime()
	{
		if (initialized)
		{
			std::cout << "\nTime already ibnitialized!";
			return true;
		}

		fpsCounter = new Text();
		if (!fpsCounter)
		{
			std::cout << "\nInitialization failed! Failed to create fpsCounter!";
			return false;
		}

		if (!fpsCounter->setFont(ginesFontPath, fpsCounterFontSize))
		{
			std::cout << "\nInitialization failed! Failed to set up fps counter!";
			return false;
		}

		fpsCounter->setColor(glm::vec4(0.12f, 0.45f, 0.07f, 1.0f));
		fpsCounter->setPosition(glm::vec2(5, WINDOW_HEIGHT - fpsCounter->getFontHeight()));

		initialized = true;
		return true;
	}
	void uninitializeTime()
	{
		if (fpsCounter != nullptr)
			delete fpsCounter;
	}

	void beginFPS()
	{
		startTicks = SDL_GetTicks();
		runTime += deltaTime / 1000.0f;

		//Update fps counter font size if needed
		if (previousFontSize != fpsCounterFontSize)
		{
			fpsCounter->setFont(ginesFontPath, fpsCounterFontSize);
			previousFontSize = fpsCounterFontSize;
		}
	}
	void endFPS()
	{
		static const int NUM_SAMPLES = 20;
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
		{
			count = currentFrame;
		}
		else
		{
			count = NUM_SAMPLES;
		}

		float deltaTimeAverage = 0;
		for (int i = 0; i < count; i++)
		{
			deltaTimeAverage += deltaTimes[i];
		}
		deltaTimeAverage /= count;

		if (deltaTimeAverage > 0)
		{
			fps = 1000.0f / deltaTimeAverage;
		}
		else
		{
			fps = 0;
		}

		static int frameCounter = 0;
		if (++frameCounter >= FPS_REFRESH_RATE)
		{
			fpsCounter->setString("FPS: " + std::to_string(int(fps)));
			frameCounter = 0;
		}

		//Limit FPS = delay return
		Uint32 frameTicks = SDL_GetTicks() - startTicks;
		if (1000.0f / maxFPS > frameTicks)
		{
			SDL_Delay(Uint32(1000.0f / maxFPS) - frameTicks);
		}

	}
	void drawFPS()
	{
		if (showFps)
		{
			fpsCounter->render();
		}
	}

}