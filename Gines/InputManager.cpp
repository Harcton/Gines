#include "InputManager.h"


InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

void InputManager::keyPress(unsigned int keyID)
{
	keyMap[keyID] = true;
}

void InputManager::keyRelease(unsigned int keyID)
{
	keyMap[keyID] = false;
}

bool InputManager::isKeyPressed(unsigned int keyID)
{
	auto it = keyMap.find(keyID);
	if (it != keyMap.end())
	{
		return it->second;
	}
	else
	{
		return false;
	}
}

void InputManager::handleInput()
{

}