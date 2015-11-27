#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>
#include "TextureCache.h"
#include "GLTexture.h"


namespace gines
{

	class ResourceManager
	{
	public:
		static GLTexture getTexture(std::string path);

	private:
		static TextureCache texCache;
	};

}

#endif