#include "ImageLoader.h"
#include "lodepng.h"
#include "IOManager.h"
#include <vector>

namespace gines
{
	GLTexture ImageLoader::loadPNG(std::string filePath)
	{
		GLTexture tex = {};

		std::vector<unsigned char> in;
		std::vector<unsigned char> out;

		unsigned int width;
		unsigned int height;

		if (IOManager::readToBuffer(filePath, in) == false) // can't read file
		{
			Message("Imageloader failed to read image to buffer!", gines::Message::Error);
		}

		int error = lodepng::decode(out, width, height, in.data(), in.size());

		if (error != 0)
		{
			Message("PNG decoding failed!", gines::Message::Error); // decode failed with: error + std::to_string(error));
		}

		glGenTextures(1, &(tex.id));

		glBindTexture(GL_TEXTURE_2D, tex.id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		return tex;
	}
}