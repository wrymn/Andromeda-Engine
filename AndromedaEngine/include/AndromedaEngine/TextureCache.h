#pragma once
#include <map>
#include "Texture.h"

namespace AndromedaEngine
{
	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();

		Texture getTexture(std::string texturePath);

	private:
		std::map <std::string, Texture> textureMap;
	};
}
