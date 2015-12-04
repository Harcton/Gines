#include "ResourceManager.h"

namespace gines
{
	TextureCache ResourceManager::texCache;

	GLTexture ResourceManager::getTexture(std::string path)
	{
		return texCache.getTexture(path);
	}
}
