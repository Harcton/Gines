#include "Error.hpp"
#include <string>
#include <iostream>
#include <vector>

#include <SDL/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Text.h"
#include "Gines.h"
#include "InputManager.h"
#include "Console.h"
#include "Time.h"
#include "Sprite.h"
#include "lodepng.h"
#include "Component.h"
#include "PhysicsComponent.h"
#include "GameObject.h"
#include "GLTexture.h"
#include "ResourceManager.h"

//DEEBUGGIA...
void handleInput();
void increaseTextCount();
bool run = true;
std::vector<gines::Text*> texts;
extern int WINDOW_HEIGHT;
//
Sprite debugsprite;
std::vector<Sprite*> sprites;
//

//Test console function
void testConsole(std::vector<std::string>& consoleWords)
{
	gines::console.log("Test command success. Other parameters used in command:");
	if (consoleWords.size() == 1)
		gines::console.log("\t[None]");

	for (unsigned i = 1; i < consoleWords.size(); i++)
	{
		gines::console.log("[" + std::to_string(i) + "] " + consoleWords[i]);
	}
}


int main(int argc, char** argv)
{
	gines::initialize();

	//GameObject Test
	gines::GameObject go;
	{
		gines::GameObject go2("go 2");
		
		go2.createChild("child");
		go2.createChild();
			go2.transform().print();
			go2.transform().move(glm::vec2(100, 150));
			go2.transform().print();
		go2.addComponent<gines::Transform>();
			go2.transform().print();
			go2.transform().move(glm::vec2(100, 150));
			go2.transform().print();
		go2.removeComponent<gines::Transform>();
			go2.transform().print();
		go2.addComponent<gines::Transform>();
		gines::GameObject* o = gines::GameObject::getGameObject("go 2");
	}
	//End Test
	


	gines::console.addConsoleCommand("test", testConsole);
	gines::console.addVariable("fps", gines::showFps);
	gines::console.addVariable("run", run);
	gines::console.addVariable("fontSize", gines::consoleFontSize);

	// Rendering debug initializations 
	sprites.push_back(new Sprite());
	sprites.back()->initialize(glm::vec2(0.0f, 0.0f), 500, 500, "Textures/mr-gines.png");
	//debugsprite.initialize(glm::vec2(1.0f, 1.0f), 1, 1, "Textures/mr-gines.png");
	
	sprites.push_back(new Sprite());
	sprites.back()->initialize(glm::vec2(-1.0f, -1.0f), 1, 1, "Textures/mr-gines.png");
	sprites.push_back(new Sprite());
	sprites.back()->initialize(glm::vec2(0.0f, -1.0f), 1, 1, "Textures/mr-gines.png");
	sprites.push_back(new Sprite());
	sprites.back()->initialize(glm::vec2(-1.0f, 0.0f), 1, 1, "Textures/mr-gines.png");

	// Rendering end 

	//Game loop
	while (run)
	{
		gines::beginMainLoop();

		//Event handling
		handleInput();

		//Sprite & shader debugging
		
		 gines::colorProgram.use();
		 glActiveTexture(GL_TEXTURE0);

		 glUniform1i(gines::colorProgram.getUniformLocation("texture1"), 0);
		 for (int i = 0; i < sprites.size(); i++)
		 {
			 sprites[i]->draw();
		 }
		 //debugsprite.draw();
		 glBindTexture(GL_TEXTURE_2D, 0);
		 gines::colorProgram.unuse();

		 //
		 go.update();
		 go.render();

		//Rendering
		for (unsigned i = 0; i < texts.size(); i++)
		{texts[i]->render();}		
		

		gines::endMainLoop();
	}

	///////DEBUG
	//Deallocate text memory...
	while (!texts.empty())
	{
		delete texts.back();
		texts.pop_back();
	}//////EoDEBUG


	return gines::uninitialize();
}




//DEEBUGGIA...
void handleInput()
{
	float moveSpeed = 5 * texts.size();
	
	if (gines::inputManager.isKeyHeld(SDLK_ESCAPE))
	{
		run = false;
		SDL_Quit();
	}
	if (gines::inputManager.isKeyPressed(SDLK_RCTRL))
	{
		increaseTextCount();
		std::cout << "\nText count increased! texts.size(): " << texts.size();
	}
	if (gines::inputManager.isKeyHeld(SDLK_UP))
	{
		for (unsigned i = 0; i < texts.size(); i++)
		{
			texts[i]->translate(glm::vec2(0, float(moveSpeed * (float(i + 1) / texts.size()))));
		}
	}
	if (gines::inputManager.isKeyHeld(SDLK_DOWN))
	{
		for (unsigned i = 0; i < texts.size(); i++)
		{
			texts[i]->translate(glm::vec2(0, float(-moveSpeed * (float(i + 1) / texts.size()))));
		}
	}
	if (gines::inputManager.isKeyHeld(SDLK_LEFT))
	{
		for (unsigned i = 0; i < texts.size(); i++)
		{
			texts[i]->translate(glm::vec2(float(-moveSpeed * (float(i + 1) / texts.size())), 0));
		}
	}
	if (gines::inputManager.isKeyHeld(SDLK_RIGHT))
	{
		for (unsigned i = 0; i < texts.size(); i++)
		{
			texts[i]->translate(glm::vec2(float(moveSpeed * (float(i + 1) / texts.size())), 0));
		}
	}
	if (gines::inputManager.isKeyHeld(SDL_BUTTON_LEFT))
	{
		glm::vec2 mouseCoordinates = gines::inputManager.getMouseCoordinates();
		std::cout << mouseCoordinates.x << "  " << mouseCoordinates.y << std::endl;
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
		glyphsToRender += texts[i]->getGlyphsToRender();
	std::cout << "\nGlyphs to render: " << glyphsToRender;
}

/////////////