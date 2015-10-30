#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include <glm\glm.hpp>
#include <unordered_map>
//#include <SDL\SDL.h>
//#include "Gines.h"
namespace gines
{

	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void update(); // For keeping track of pressed keys


		void keyPress(unsigned int keyID);
		void keyRelease(unsigned int keyID);
		void setMouseCoordinates(float x, float y);

		// Returns true if a key is held down

		bool isKeyHeld(unsigned int keyID);

		// Returns true if a key was just pressed

		bool isKeyPressed(unsigned int keyID);

		// Gets
		glm::vec2 getMouseCoordinates() const { return mouseCoordinates; };

	private:
		std::unordered_map <unsigned int, bool> keyMap;
		std::unordered_map <unsigned int, bool> previousKeyMap;
		
		glm::vec2 mouseCoordinates;

		bool wasKeyHeld(unsigned int keyID);
	};
}

#endif


// https://www.youtube.com/watch?v=Epyih-LEbig