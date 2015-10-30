#ifndef TIME_H
#define TIME_H
#include <SDL\SDL_stdinc.h>



namespace gines
{
	//Variables that should be visible outside
	extern float fps;
	extern float maxFPS;
	extern Uint32 deltaTime;

	bool initializeTime();
	void uninitializeTime();
	void beginFPS();
	void endFPS();
	void drawFPS();

}

#endif