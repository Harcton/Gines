#include "IOManager.h"
#include "Error.hpp"

namespace gines
{
	//Reads a file to a buffer
	bool IOManager::readToBuffer(std::string filePath, std::vector<unsigned char>& buffer)
	{
		std::ifstream file(filePath, std::ios::binary);

		if (file.fail())
		{
			Message("IOManager failed to read file!", gines::Message::Error);
			perror(filePath.c_str());
			return false;
		}

		//Seek to the end
		file.seekg(0, std::ios::end);
		//Get file size
		int fileSize = file.tellg();
		//Seek back to the beginning
		file.seekg(0, std::ios::beg);
		//Reduce file size by any possible header bytes.
		fileSize -= file.tellg();

		buffer.resize(fileSize);
		file.read((char*)&(buffer[0]), fileSize);
		file.close();

		return true; // Success.
	}
}