#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include "Error.hpp"
#include "GLTexture.h"
#include <string>

namespace gines
{
	class ImageLoader
	{
	public:

		static GLTexture loadPNG(std::string filePath);

	};
}

#endif