//#pragma region PreProcessor
//
//#include "ResourceManager.h"
//
//
//
//#define AUTONAME(T_NAME)\
//		string Name = #T_NAME;\
//		for (int a = 1; a <= 4; a++) {\
//		if (T_NAME ## No < (10 ^ a)) {\
//		Name += "0";}}\
//		Name += to_string(T_NAME ## No);
//
//
//#define AUTOIDENTIFIER(T_NAME)\
//		int Identifier = T_NAME ## No + 10000;
//
//
//#define ADDDATA(T_NAME)\
//		T_NAME ## s.push_back(new ## T_NAME);\
//		T_NAME ## Names.push_back(Name);\
//		T_NAME ## Identifiers.push_back(Identifier);\
//		T_NAME ## Filenames.push_back(Filename);\
//		T_NAME ## No++;
//
//
//#define FIND(T_NAME, TYPE, T_SEARCH, P_SEARCH)\
//		list< ## TYPE ## >::iterator tit = T_NAME ## s.begin();\
//		for (list< ## T_SEARCH ## >::iterator it = T_NAME ## P_SEARCH ## s.begin(); it != T_NAME ## P_SEARCH ## s.end(); ++it) {\
//		if (*it == ## P_SEARCH) {return *tit;}\
//		++tit;}\
//		cout << "Error: Couldn't find a ## T_NAME ## with ## P_SEARCH ## '" << ## P_SEARCH ## << "'.\n";\
//		return 0;
//
//
//
//#define REMOVE(T_NAME, TYPE, COMPARE_A, COMPARE_B)\
//	list<## TYPE ##>::iterator ia = T_NAME ## s.begin();\
//	list<string>::iterator ic = T_NAME ##Names.begin();\
//	list<int>::iterator id = T_NAME ##Identifiers.begin();\
//	list<string>::iterator ie = T_NAME ##Filenames.begin();\
//	while (COMPARE_A != T_NAME ## COMPARE_B ## s.end() && * ## COMPARE_A != Deletable){\
//	++ia;++ic;++id;++ie;}\
//	if (COMPARE_A != T_NAME ## COMPARE_B ## s.end()){\
//	destroy ## T_NAME ## (*ia);\
//	T_NAME ## s.erase(ia);\
//	T_NAME ## Names.erase(ic);\
//	T_NAME ## Identifiers.erase(id);\
//	T_NAME ## Filenames.erase(ie);\
//	T_NAME ## No--;\
//	return true;}return false;				
//
//
//
//#define POPULATE(T_NAME, TYPE)\
//	bool ResourceManager::add ## T_NAME ## (string Filename){AUTONAME(T_NAME);return add ## T_NAME ## (Filename, Name);}\
//	bool ResourceManager::add ## T_NAME ## (string Filename, int Identifier){AUTONAME(T_NAME);return create ## T_NAME ## (Filename, Identifier, Name);}\
//	bool ResourceManager::add ## T_NAME ## (string Filename, string Name){AUTOIDENTIFIER(T_NAME);return create ## T_NAME ## (Filename, Identifier, Name);}\
//	bool ResourceManager::add ## T_NAME ## (string Filename, int Identifier, string Name){return ResourceManager::create ## T_NAME ## (Filename, Identifier, Name);}\
//	TYPE ResourceManager::find ## T_NAME ## (int Identifier){FIND(T_NAME, TYPE, int, Identifier);}\
//	TYPE ResourceManager::find ## T_NAME ## (string Name){FIND(T_NAME, TYPE, string, Name);}\
//	TYPE ResourceManager::find ## T_NAME ## (int Identifier, string Name){TYPE a = find ## T_NAME ## (Identifier); TYPE b = find ## T_NAME ## (Name); return (a == b) ? a : 0;}\
//	bool ResourceManager::remove ## T_NAME ## (TYPE Deletable){REMOVE(T_NAME, TYPE, ia, );}\
//	bool ResourceManager::remove ## T_NAME ## (int Deletable){REMOVE(T_NAME, TYPE, id, Identifier);}\
//	bool ResourceManager::remove ## T_NAME ## (string Deletable){REMOVE(T_NAME, TYPE, ic, Name);}
//
//#pragma endregion
//
//ResourceManager::ResourceManager()
//{
//	TextFileNo = 0;
//	TextureNo = 0;
//}
//ResourceManager::~ResourceManager()
//{
//	for (list<list<string>*>::iterator tit = TextFiles.begin(); tit != TextFiles.end(); ++tit) {
//		destroyTextFile(*tit);
//	}
//
//	for (list<GLuint>::iterator tit = Textures.begin(); tit != Textures.end(); ++tit) {
//		destroyTexture(*tit);
//	}
//}
//
//bool ResourceManager::createTextFile(string Filename, int Identifier, string Name)
//{
//	string line;
//
//	ifstream myfile("example.txt");
//
//	if (myfile.is_open())
//	{
//		list<string> newList;
//		int length = 0;
//
//		while (getline(myfile, line))
//		{
//			newList.push_back(line);
//			length++;
//		}
//		myfile.close();
//
//		TextFiles.push_back(&newList);
//		TextFileLengths.push_back(length);
//		TextFileNames.push_back(Name);
//		TextFileIdentifiers.push_back(Identifier);
//		TextFileFilenames.push_back(Filename);
//		TextFileNo++;
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
//void ResourceManager::destroyTextFile(list<string>* Deletable)
//{
//	delete &Deletable;
//}
//
//POPULATE(TextFile, list<string>*);
//
//bool ResourceManager::createTexture(string Filename, int Identifier, string Name)
//{
//	SDL_Surface* surface = IMG_Load(Filename.c_str());
//
//	if (!surface) {
//		cout << "Error: File '" << Filename << "' NULL\n";
//		return false;
//	}
//
//	GLuint newTexture = surfaceToTexture(surface);
//
//	SDL_FreeSurface(surface);
//
//	if (newTexture == 0){
//		cout << "Error: Texture '" << Filename << "' NULL\n";
//		return false;
//	}
//	ADDDATA(Texture);
//	return true;
//}
//void ResourceManager::destroyTexture(GLuint Deletable)
//{
//	glDeleteTextures(1, &Deletable);
//}
//GLuint ResourceManager::surfaceToTexture(SDL_Surface* surface)
//{
//	GLuint TextureID = 0;
//
//	glGenTextures(1, &TextureID);
//	glBindTexture(GL_TEXTURE_2D, TextureID);
//
//	int Mode = GL_RGB;
//
//	if (surface->format->BytesPerPixel == 4) {
//		Mode = GL_RGBA;
//	}
//
//	glTexImage2D(GL_TEXTURE_2D, 0, Mode, surface->w, surface->h, 0, Mode, GL_UNSIGNED_BYTE, surface->pixels);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	return TextureID;
//}
//
//POPULATE(Texture, GLuint);
//
//bool ResourceManager::createSound(string Filename, int Identifier, string Name)
//{
//	Mix_Chunk* newSound = Mix_LoadWAV(Filename.c_str());
//	if (newSound == NULL)
//	{
//		cout << "Failed to load sound effect from " << Filename << "! SDL_mixer Error: %s\n", Mix_GetError();
//		return false;
//	}
//
//	ADDDATA(Sound);
//	return true;
//}
//void ResourceManager::destroySound(Mix_Chunk* Deletable)
//{
//	Mix_FreeChunk(Deletable);
//}
//
//POPULATE(Sound, Mix_Chunk*)
//
//bool ResourceManager::createMusic(string Filename, int Identifier, string Name)
//{
//	//Load music
//	Mix_Music* newMusic = Mix_LoadMUS(Filename.c_str());
//	if (newMusic == NULL)
//	{
//		cout << "Failed to load music from " << Filename << "! SDL_mixer Error: %s\n", Mix_GetError();
//		return false;
//	}
//
//	ADDDATA(Music);
//	return true;
//}
//void ResourceManager::destroyMusic(Mix_Music* Deletable)
//{
//	Mix_FreeMusic(Deletable);
//}
//
//POPULATE(Music, Mix_Music*)
//
//
//
