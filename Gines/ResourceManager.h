#pragma once
#include <SDL/SDL.h>
#include <fstream>
#include <conio.h>
#include <iostream>
//#include <SDL_image.h> NOT FOUND?
#include <list>
#include <string>

using namespace std;

namespace gines
{

	class ResourceManager
	{
	public:
		ResourceManager();
		~ResourceManager();

		list<list<string>*> textFiles;
		list<int> textFileLengths;
		list<string> textFileNames;
		list<int> textFileIdentifiers;
		list<string> texFileFilenames;
		int textFileNo;



		//list<SDL_Texture*> textures;
		//list<string> textureNames;
		//list<int> textureIdentifiers;
		//list<string> textureFilenames;
		//int textureNo;





		bool AddTextFile(string Filename);
		bool AddTextFile(string Filename, int Identifier);
		bool AddTextFile(string Filename, string Name);
		bool AddTextFile(string Filename, int Identifier, string Name);

		list<string>* FindTextFile(int Identifier);
		list<string>* FindTextFile(string Name);
		list<string>* FindTextFile(int Identifier, string Name);

		bool RemoveTextFile(list<string>* Deletable);
		bool RemoveTextFile(int Identifier);
		bool RemoveTextFile(string Name);
		bool RemoveTextFile(int Identifier, string Name);




		//bool AddTexture(string Filename);
		//bool AddTexture(string Filename, int Identifier);
		//bool AddTexture(string Filename, string Name);
		//bool AddTexture(string Filename, int Identifier, string Name);

		//SDL_Texture* FindTexture(int Identifier);
		//SDL_Texture* FindTexture(string Name);
		//SDL_Texture* FindTexture(int Identifier, string Name);

		//bool RemoveTexture(int Identifier);
		//bool RemoveTexture(string Name);
		//bool RemoveTexture(int Identifier, string Name);
	};

}