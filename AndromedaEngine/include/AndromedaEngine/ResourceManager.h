#pragma once
#include "TextureCache.h"
#include "Texture.h"

namespace AndromedaEngine
{
	class ResourceManager
	{
	public:
		//Returns Texture fropm given file path. Use .id variable to get Gluint ID of texture
		static Texture getTexture(std::string texturePath);

	private:
		static TextureCache textureCache;
	};
}
