#include "ResourceManager.h"

namespace AndromedaEngine
{
	TextureCache ResourceManager::textureCache;

	//RETURNS NEW TEXTURE OR CACHED TEXTURE FROM MAP
	Texture ResourceManager::getTexture(std::string texturePath)
	{
		return textureCache.getTexture(texturePath);
	}
}