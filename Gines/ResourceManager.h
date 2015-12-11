#pragma once

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

