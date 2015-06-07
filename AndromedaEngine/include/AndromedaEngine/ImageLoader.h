#pragma once
#include "Texture.h"
#include <string>

namespace AndromedaEngine
{
	class ImageLoader
	{
	public:
		static Texture loadPNG(std::string filePath);
	};
}
