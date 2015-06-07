#pragma once
#include <vector>
#include <GL\glew.h>
#include <SDL2\SDL.h>

namespace AndromedaEngine
{
	class IOManager
	{
	public:
		static bool readFileToBuffer(std::vector<unsigned char>& buffer, std::string filePath);
	};
}
