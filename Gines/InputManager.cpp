#include "InputManager.h"


InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

void InputManager::update()
{
	// Copying keyMap to previousKeyMap using for_each loop
	for (auto& it: keyMap)
	{
		previousKeyMap[it.first] = it.second;
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

bool InputManager::isKeyPressed(unsigned int keyID)
{	//Checks if the key was pressed this frame and WASN'T last frame.
	bool isPressed;
	if (isKeyHeld(keyID) == true && wasKeyHeld(keyID) == false )
	{
		return true;
	}
	return false;
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

