#ifndef IOMANAGER_H
#define IOMANAGER_H
#include <vector>
#include <string>
#include <fstream>

// Static class, no need for multiple instances of this class

class IOManager
{
public:

	//Reads file to a buffer
	static bool readToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
};

#endif
