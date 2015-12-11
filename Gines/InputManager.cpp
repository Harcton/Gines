#include "InputManager.h"
#include "Gines.h"
#include <SDL/SDL_events.h>
#include <SDL\SDL.h>
#include <iostream>

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

namespace gines
{
	InputManager::InputManager() : mouseCoordinates(0.0f)
	{
	}


	InputManager::~InputManager()
	{
	}

	void InputManager::update()
	{
		// Copying keyMap to previousKeyMap using for_each loop
		for (auto& it : keyMap)
		{
			previousKeyMap[it.first] = it.second;
		}

		static SDL_Event mEvent;
		while (SDL_PollEvent(&mEvent))
		{
			switch (mEvent.type)
			{
			default:
				break;
			case SDL_KEYDOWN:
				inputManager.keyPress(mEvent.key.keysym.sym);
				break;
			case SDL_KEYUP:
				inputManager.keyRelease(mEvent.key.keysym.sym);
				break;
			case SDL_MOUSEMOTION:
				inputManager.setMouseCoordinates(mEvent.motion.x, mEvent.motion.y);
				break;
			case SDL_MOUSEBUTTONDOWN:
				inputManager.keyPress(mEvent.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				inputManager.keyRelease(mEvent.button.button);
				break;
			case SDL_QUIT:
				SDL_Quit();
				break;
			}
			
		}
	}

	void InputManager::keyPress(unsigned int keyID)
	{
		keyMap[keyID] = true;
	}

	void InputManager::keyRelease(unsigned int keyID)
	{
		keyMap[keyID] = false;
	}

	void InputManager::setMouseCoordinates(float x, float y)
	{
		mouseCoordinates.x = x;
		mouseCoordinates.y = (y - WINDOW_HEIGHT) * -1;
	}

	bool InputManager::isKeyHeld(unsigned int keyID)
	{
		auto it = keyMap.find(keyID);
		if (it != keyMap.end())
		{ // Found key
			return it->second;
		}
		else
		{ // Didn't find key
			return false;
		}
	}

	bool InputManager::wasKeyHeld(unsigned int keyID)
	{
		auto it = previousKeyMap.find(keyID);
		if (it != previousKeyMap.end())
		{ // Found key
			return it->second;
		}
		else
		{ // Didn't find key
			return false;
		}
	}

	bool InputManager::isKeyPressed(unsigned int keyID)
	{	//Checks if the key was pressed this frame and WASN'T last frame.
		if (isKeyHeld(keyID) == true && wasKeyHeld(keyID) == false)
		{
			return true;
		}
		return false;
	}
}
