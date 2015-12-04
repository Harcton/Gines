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
#include "ImageLoader.h"
#include "Camera.h"

//DEEBUGGIA...
void handleInput();
void increaseTextCount();
bool run = true;
std::vector<gines::Text*> texts;
extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;
gines::GameObject go;
gines::GameObject camera1;
gines::GameObject camera2;
gines::GameObject camera3;
gines::GameObject camera4;

//
gines::Sprite sprite;
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

	//Camera test
	camera1.addComponent<gines::Transform>();
	camera1.addComponent<gines::Camera>();
	camera1.getComponent<gines::Camera>()->setViewport(glm::vec2(WINDOW_WIDTH*0.0f, WINDOW_HEIGHT*0.5f), glm::vec2(WINDOW_WIDTH*0.25f, WINDOW_HEIGHT*0.25f));
	camera1.addComponent<gines::Text>();
	camera1.getComponent<gines::Text>()->setFont(gines::ginesFontPath, 50);
	camera1.getComponent<gines::Text>()->setString("_C1");
	camera1.getComponent<gines::Text>()->setColor(1.0f, 0.6f, 0.0f);
	camera2.addComponent<gines::Transform>();
	camera2.addComponent<gines::Camera>();
	camera2.getComponent<gines::Camera>()->setViewport(glm::vec2(WINDOW_WIDTH*0.5f, WINDOW_HEIGHT*0.5f), glm::vec2(WINDOW_WIDTH*0.5f, WINDOW_HEIGHT*0.5f));
	camera2.addComponent<gines::Text>();
	camera2.getComponent<gines::Text>()->setFont(gines::ginesFontPath, 50);
	camera2.getComponent<gines::Text>()->setString("_C2");
	camera2.getComponent<gines::Text>()->setColor(0.0f, 0.6f, 0.0f);
	camera3.addComponent<gines::Transform>();
	camera3.addComponent<gines::Camera>();
	camera3.getComponent<gines::Camera>()->setViewport(glm::vec2(WINDOW_WIDTH*0.0f, WINDOW_HEIGHT*0.0f), glm::vec2(WINDOW_WIDTH*0.5f, WINDOW_HEIGHT*0.5f));
	camera3.addComponent<gines::Text>();
	camera3.getComponent<gines::Text>()->setFont(gines::ginesFontPath, 50);
	camera3.getComponent<gines::Text>()->setString("_C3");
	camera3.getComponent<gines::Text>()->setColor(0.0f, 0.6f, 0.0f);
	camera4.addComponent<gines::Transform>();
	camera4.addComponent<gines::Camera>();
	camera4.getComponent<gines::Camera>()->setViewport(glm::vec2(WINDOW_WIDTH*0.5f, WINDOW_HEIGHT*0.0f), glm::vec2(WINDOW_WIDTH*0.33f, WINDOW_HEIGHT*0.33f));
	camera4.addComponent<gines::Text>();
	camera4.getComponent<gines::Text>()->setFont(gines::ginesFontPath, 50);
	camera4.getComponent<gines::Text>()->setString("_C4");
	camera4.getComponent<gines::Text>()->setColor(0.0f, 0.6f, 0.0f);
		
	//GameObject Test
	go.addComponent<gines::Transform>();
	go.addComponent<gines::Text>();
	gines::Text& textComponentReference = *go.getComponent<gines::Text>();
	textComponentReference.setFont(gines::ginesFontPath, 50);
	textComponentReference.setString("Game object text component");
	textComponentReference.setColor(1.0f, 0.6f, 0.0f);
	//End Test
	


	//Console commands
	gines::console.addConsoleCommand("test", testConsole);
	gines::console.addVariable("fps", gines::showFps);
	gines::console.addVariable("run", run);
	gines::console.addVariable("fontSize", gines::consoleFontSize);

	// Rendering debug initializations
	camera1.addComponent<gines::Sprite>();
	camera1.getComponent<gines::Sprite>()->initialize(glm::vec2(-1.0f, -1.0f), 100, 100, "Textures/mr-gines.png");
	/******************************/sprite.initialize(glm::vec2(-1.0f, -1.0f), 100, 100, "Textures/mr-gines.png");
	camera1.getComponent<gines::Sprite>()->setOrigin(50, 50);

	
	// Rendering end 

	//Game loop
	while (run)
	{
		gines::beginMainLoop();

		//Event handling
		handleInput();
		//go.transform().print();

		//Sprite & shader debugging
		
		 //sprite.render();

		 //
		 go.update();
		 go.render();
		 camera1.update();
		 camera2.update();
		 camera3.update();
		 camera4.update();
		 camera1.render();
		 camera2.render();
		 camera3.render();
		 camera4.render();

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
		go.transform().move(glm::vec2(0, 1));
		for (unsigned i = 0; i < texts.size(); i++)
		{
			texts[i]->translate(glm::vec2(0, float(moveSpeed * (float(i + 1) / texts.size()))));
		}
	}
	if (gines::inputManager.isKeyHeld(SDLK_DOWN))
	{
		go.transform().move(glm::vec2(0, -1));
		for (unsigned i = 0; i < texts.size(); i++)
		{
			texts[i]->translate(glm::vec2(0, float(-moveSpeed * (float(i + 1) / texts.size()))));
		}
	}
	if (gines::inputManager.isKeyHeld(SDLK_LEFT))
	{
		go.transform().move(glm::vec2(-1, 0));
		for (unsigned i = 0; i < texts.size(); i++)
		{
			texts[i]->translate(glm::vec2(float(-moveSpeed * (float(i + 1) / texts.size())), 0));
		}
	}
	if (gines::inputManager.isKeyHeld(SDLK_RIGHT))
	{
		go.transform().move(glm::vec2(1, 0));
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

	//Camera movement
	if (gines::inputManager.isKeyHeld(SDLK_z))
		camera1.transform().rotate(0.1f);
	if (gines::inputManager.isKeyHeld(SDLK_x))
		camera1.transform().rotate(-0.1f);
	if (gines::inputManager.isKeyHeld(SDLK_w))
		camera1.transform().move(glm::vec2(0, 1));
	if (gines::inputManager.isKeyHeld(SDLK_s))
		camera1.transform().move(glm::vec2(0, -1));
	if (gines::inputManager.isKeyHeld(SDLK_d))
		camera1.transform().move(glm::vec2(1, 0));
	if (gines::inputManager.isKeyHeld(SDLK_a))
		camera1.transform().move(glm::vec2(-1, 0));
	if (gines::inputManager.isKeyHeld(SDLK_e))
		camera1.getComponent<gines::Camera>()->setScale(camera1.getComponent<gines::Camera>()->getScale() + 0.01f);
	if (gines::inputManager.isKeyHeld(SDLK_q))
		camera1.getComponent<gines::Camera>()->setScale(camera1.getComponent<gines::Camera>()->getScale() - 0.01f);

	//Camera2 movement
	if (gines::inputManager.isKeyHeld(SDLK_i))
		camera2.transform().move(glm::vec2(0, 1));
	if (gines::inputManager.isKeyHeld(SDLK_k))
		camera2.transform().move(glm::vec2(0, -1));
	if (gines::inputManager.isKeyHeld(SDLK_l))
		camera2.transform().move(glm::vec2(1, 0));
	if (gines::inputManager.isKeyHeld(SDLK_j))
		camera2.transform().move(glm::vec2(-1, 0));
	if (gines::inputManager.isKeyHeld(SDLK_o))
		camera2.getComponent<gines::Camera>()->setScale(camera2.getComponent<gines::Camera>()->getScale() + 0.01f);
	if (gines::inputManager.isKeyHeld(SDLK_u))
		camera2.getComponent<gines::Camera>()->setScale(camera2.getComponent<gines::Camera>()->getScale() - 0.01f);

	//Camera3 movement
	if (gines::inputManager.isKeyHeld(SDLK_UP))
		camera3.transform().move(glm::vec2(0, 1));
	if (gines::inputManager.isKeyHeld(SDLK_DOWN))
		camera3.transform().move(glm::vec2(0, -1));
	if (gines::inputManager.isKeyHeld(SDLK_RIGHT))
		camera3.transform().move(glm::vec2(1, 0));
	if (gines::inputManager.isKeyHeld(SDLK_LEFT))
		camera3.transform().move(glm::vec2(-1, 0));
	if (gines::inputManager.isKeyHeld(SDLK_PAGEUP))
		camera3.getComponent<gines::Camera>()->setScale(camera3.getComponent<gines::Camera>()->getScale() + 0.01f);
	if (gines::inputManager.isKeyHeld(SDLK_PAGEDOWN))
		camera3.getComponent<gines::Camera>()->setScale(camera3.getComponent<gines::Camera>()->getScale() - 0.01f);

	//Camera4 movement
	if (gines::inputManager.isKeyHeld(SDLK_KP_8))
		camera4.transform().move(glm::vec2(0, 1));
	if (gines::inputManager.isKeyHeld(SDLK_KP_5))
		camera4.transform().move(glm::vec2(0, -1));
	if (gines::inputManager.isKeyHeld(SDLK_KP_6))
		camera4.transform().move(glm::vec2(1, 0));
	if (gines::inputManager.isKeyHeld(SDLK_KP_4))
		camera4.transform().move(glm::vec2(-1, 0));
	if (gines::inputManager.isKeyHeld(SDLK_KP_9))
		camera4.getComponent<gines::Camera>()->setScale(camera4.getComponent<gines::Camera>()->getScale() + 0.01f);
	if (gines::inputManager.isKeyHeld(SDLK_KP_7))
		camera4.getComponent<gines::Camera>()->setScale(camera4.getComponent<gines::Camera>()->getScale() - 0.01f);

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