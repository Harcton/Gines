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

	void keyPress(unsigned int keyID);
	void keyRelease(unsigned int keyID);
	void handleInput();

	bool isKeyPressed(unsigned int keyID);

private:
	std::unordered_map <unsigned int, bool> keyMap;

};

#endif


// https://www.youtube.com/watch?v=Epyih-LEbig