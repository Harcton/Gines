#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>
TextureCache::TextureCache()
{
}


TextureCache::~TextureCache()
{
}

GLTexture TextureCache::getTexture(std::string path)
{
	//checks for the texture to see if it's in the map
	auto mapIt = textureMap.find(path);

	//check if the texture isn't in the map
	if (mapIt == textureMap.end())
	{
		//load texture
		GLTexture newTex = gines::ImageLoader::loadPNG(path);
		//insert it into the map
		std::pair<std::string, GLTexture> texPair(path, newTex);
		textureMap.insert(texPair);
		std::cout << "\nUsing cached texture\n";
		return newTex;
		
	}
	//returns the texture
	std::cout << "\nFound texture in map! Using...\n";
	return mapIt->second;

}