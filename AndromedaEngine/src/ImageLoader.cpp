#include "ImageLoader.h"
#include "Picopng.h"
#include "IOManager.h"
#include "Errors.h"

namespace AndromedaEngine
{
	Texture ImageLoader::loadPNG(std::string filePath)
	{
		Texture texture;

		std::vector<unsigned char> in;
		std::vector<unsigned char> out;

		unsigned long width, height;

		Error(!IOManager::readFileToBuffer(in, filePath), "Failed to load PNG into buffer at " + filePath, true);

		GLbyte errorCode = decodePNG(out, width, height, &in[0], in.size());
		Error(errorCode != 0, "Failed to decode PNG from fileapth: " + filePath + "\n Error code:" + std::to_string(errorCode), true);

		glGenTextures(1, &(texture.id));
		glBindTexture(GL_TEXTURE_2D, texture.id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

		glTextureParameteri(texture.id, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(texture.id, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTextureParameteri(texture.id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(texture.id, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		texture.width = width;
		texture.height = height;

		return texture;
	}
}