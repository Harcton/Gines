#pragma once

#include <map>
#include <GL\glew.h>
#include "GLTexture.h"

class TextureCache
{
public:
	TextureCache();
	~TextureCache();

	GLTexture getTexture(std::string path);

private:
	std::map<std::string, GLTexture> textureMap;
};
