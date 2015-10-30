#include <SDL\SDL_timer.h>
#include <iostream>

#include "Time.h"
#include "Text.h"



namespace gines
{
	float fps = 0;
	float maxFPS = 60;
	Uint32 deltaTime = 0;
	float runTime = 0;
	Uint32 startTicks = 0;
	gines::Text* fpsCounter;
	bool initialized = false;



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

		if (!fpsCounter->setFont("Fonts/Anonymous.ttf", 40))
		{
			std::cout << "\nInitialization failed! Failed to set up fps counter!";
			return false;
		}

		fpsCounter->setColor(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));

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
	}
	void endFPS()
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




		fpsCounter->setString("FPS: ");//std::to_string(fps));
		fpsCounter->render();

		//Limit FPS = delay return
		Uint32 frameTicks = SDL_GetTicks() - startTicks;
		if (1000.0f / maxFPS > frameTicks)
			SDL_Delay(Uint32(1000.0f / maxFPS) - frameTicks);
	}


}