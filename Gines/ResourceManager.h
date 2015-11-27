#pragma region PreProcessor

#pragma once
#include <SDL/SDL.h>
#include <fstream>
#include <conio.h>
#include <iostream>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <list>
#include <string>

using namespace std;

#define CREATESTOOFS(T_NAME, TYPE)\
		list< ## TYPE ## > T_NAME ## s;\
		list<string> T_NAME ## Names;\
		list<int> T_NAME ## Identifiers;\
		list<string> T_NAME ## Filenames;\
		int T_NAME ## No;\
		bool add ## T_NAME ## (string Filename);\
		bool add ## T_NAME ## (string Filename, int Identifier);\
		bool add ## T_NAME ## (string Filename, string Name);\
		bool add ## T_NAME ## (string Filename, int Identifier, string Name);\
		bool create ## T_NAME ## (string Filename, int Identifier, string Name);\
		TYPE find ## T_NAME ## (int Identifier);\
		TYPE find ## T_NAME ## (string Name);\
		TYPE find ## T_NAME ## (int Identifier, string Name);\
		void destroy ## T_NAME ## (TYPE Deletable);\
		bool remove ## T_NAME ## (TYPE Deletable);\
		bool remove ## T_NAME ## (int Deletable);\
		bool remove ## T_NAME ## (string Deletable);\

#pragma endregion

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	CREATESTOOFS(TextFile, list<string>*);
	list<int> TextFileLengths;

	CREATESTOOFS(Texture, GLuint);
	GLuint surfaceToTexture(SDL_Surface* surface);

	CREATESTOOFS(Sound, Mix_Chunk*);
	CREATESTOOFS(Music, Mix_Music*);

	//Projektiin lisättävä SDL_image ja SDL_mixer
};

