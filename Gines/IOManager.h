#pragma once

#include <vector>
#include <string>
#include <fstream>

// Static class, no need for multiple instances of this class

namespace gines
{
	class IOManager
	{
	public:

		//Reads file to a buffer
		static bool readToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
	};
}
