#include "ResourceManager.h"


ResourceManager::ResourceManager()
{
	textFileNo = 0;
	//textureNo = 0;
}


ResourceManager::~ResourceManager()
{
	for (list<list<string>*>::iterator tit = textFiles.begin(); tit != textFiles.end(); ++tit) {
		delete *tit;
	} 
}


bool ResourceManager::AddTextFile(string Filename)
{
	int Identifier = textFileNo + 10000;

	return AddTextFile(Filename, Identifier);
}
bool ResourceManager::AddTextFile(string Filename, int Identifier)
{
	string Name = "TextFile";
	for (int a = 1; a < 4; a++) {
		if (Identifier < 10 ^ a) {
			Name += "0";
		}
	}
	Name += to_string(Identifier);

	return AddTextFile(Filename, Identifier, Name);
}
bool ResourceManager::AddTextFile(string Filename, string Name)
{
	int Identifier = textFileNo + 10000;

	return AddTextFile(Filename, Identifier, Name);
}
bool ResourceManager::AddTextFile(string Filename, int Identifier, string Name)
{
	string line;

	ifstream myfile("example.txt");

	if (myfile.is_open())
	{
		list<string> newList;
		int length = 0;

		while (getline(myfile, line))
		{
			newList.push_back(line);
			length++;
		}
		myfile.close();
		textFiles.push_back(&newList);
		textFileLengths.push_back(length);

		textFileNames.push_back(Name);
		textFileIdentifiers.push_back(Identifier);
		texFileFilenames.push_back(Filename);
		textFileNo++;
		return true;
	}
	else
	{
		return false;
	}
}

list<string>* ResourceManager::FindTextFile(int Identifier)
{
	list<list<string>*>::iterator tit = textFiles.begin();

	for (list<int>::iterator it = textFileIdentifiers.begin(); it != textFileIdentifiers.end(); ++it) {
		if (*it == Identifier) {
			return *tit;
		}
		++tit;
	}

	return NULL;
}
list<string>* ResourceManager::FindTextFile(string Name)
{
	list<list<string>*>::iterator tit = textFiles.begin();

	for (list<string>::iterator it = textFileNames.begin(); it != textFileNames.end(); ++it) {
		if (*it == Name) {
			return *tit;
		}
		++tit;
	}

	return NULL;
}
list<string>* ResourceManager::FindTextFile(int Identifier, string Name)
{
	list<string>* a = FindTextFile(Identifier);
	list<string>* b = FindTextFile(Name);

	return (a == b) ? a : NULL;
}


bool ResourceManager::RemoveTextFile(list<string>* Deletable)
{
	list<list<string>*>::iterator ia = textFiles.begin();
	list<int>::iterator ib = textFileLengths.begin();
	list<string>::iterator ic = textFileNames.begin();
	list<int>::iterator id = textFileIdentifiers.begin();
	list<string>::iterator ie = texFileFilenames.begin();

	while (ia != textFiles.end() && *ia != Deletable)
	{
		++ia;
		++ib;
		++ic;
		++id;
		++ie;
	}

	if (ia != textFiles.end())
	{
		delete *ia;
		
		textFiles.erase(ia);
		textFileLengths.erase(ib);
		textFileNames.erase(ic);
		textFileIdentifiers.erase(id);
		texFileFilenames.erase(ie);
		textFileNo--;

		return true;
	}

	return false;
}

bool ResourceManager::RemoveTextFile(int Identifier)
{
	list<string>* deletable = FindTextFile(Identifier);

	if (deletable != NULL) {
		return RemoveTextFile(deletable);
	}

	return false;
}
bool ResourceManager::RemoveTextFile(string Name)
{
	list<string>* deletable = FindTextFile(Name);

	if (deletable != NULL) {
		return RemoveTextFile(deletable);
	}

	return false;
}
bool ResourceManager::RemoveTextFile(int Identifier, string Name)
{
	list<string>* deletable = FindTextFile(Identifier, Name);
	
	if (deletable != NULL) {
		return RemoveTextFile(deletable);
	}

	return false;
}




//bool ResourceManager::AddTexture(string Filename)
//{
//
//}
//bool ResourceManager::AddTexture(string Filename, int Identifier)
//{
//
//}
//bool ResourceManager::AddTexture(string Filename, string Name)
//{
//
//}
//bool ResourceManager::AddTexture(string Filename, int Identifier, string Name)
//{
//
//}
//
//SDL_Texture* ResourceManager::FindTexture(int Identifier)
//{
//
//}
//SDL_Texture* ResourceManager::FindTexture(string Name)
//{
//
//}
//SDL_Texture* ResourceManager::FindTexture(int Identifier, string Name)
//{
//
//}
