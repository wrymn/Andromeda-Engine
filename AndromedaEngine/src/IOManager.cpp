#include "IOManager.h"
#include <fstream>
#include "Errors.h"

namespace AndromedaEngine
{
	bool IOManager::readFileToBuffer(std::vector<unsigned char>& buffer, std::string filePath)
	{
		std::ifstream file(filePath, std::ios::binary);
		if (file.fail())
		{
			Error(true, "Failed to open file from " + filePath);
			return false;
		}

		//Seek from the start to the end of the file
		file.seekg(0, std::ios::end);
		//Get the file size
		int fileSize = file.tellg();

		//Go to the start of file
		file.seekg(0, std::ios::beg);

		buffer.resize(fileSize);
		file.read((char *)&buffer[0], fileSize);
		file.close();

		return true;
	}
}