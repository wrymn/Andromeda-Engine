#include "TextureCache.h"
#include "Errors.h"
#include "ImageLoader.h"
#include <iostream>

namespace AndromedaEngine
{
	TextureCache::TextureCache()
	{
	}


	TextureCache::~TextureCache()
	{
	}

	//RETURNS NEW TEXTURE OR CACHED TEXTURE FROM MAP
	Texture TextureCache::getTexture(std::string texturePath)
	{
		//1. Scan textureMap for texture
		auto mit = textureMap.find(texturePath);

		//2. Check if its not in map
		if (mit == textureMap.end())
		{
			Texture newTexture = ImageLoader::loadPNG(texturePath);
			//Create new pair for created texture
			//Insert it into textureMap
			textureMap.insert(make_pair(texturePath, newTexture));

			// 3. Return Texture
			return newTexture;
		}

		// 3. Return second pair(texture itself) from textureMap 
		return mit->second;
	}
}