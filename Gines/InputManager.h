#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <unordered_map>
//#include <SDL\SDL.h>
//#include "Gines.h"

class InputManager
{
public:
	InputManager();
	~InputManager();

	void update(); // For keeping track of pressed keys


	void keyPress(unsigned int keyID);
	void keyRelease(unsigned int keyID);
	void handleInput();

	// Returns true if a key is held down

	bool isKeyHeld(unsigned int keyID);

	// Returns true if a key was just pressed

	bool isKeyPressed(unsigned int keyID);

private:
	std::unordered_map <unsigned int, bool> keyMap;
	std::unordered_map <unsigned int, bool> previousKeyMap;

	bool wasKeyHeld(unsigned int keyID);
};

#endif


// https://www.youtube.com/watch?v=Epyih-LEbig