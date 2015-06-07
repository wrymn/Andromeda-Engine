#pragma once
#include <SDL2\SDL.h>
#include <GL\glew.h>
#include <string>
#include "Texture.h"

/*
	LEGACY CLASS
*/

namespace AndromedaEngine
{
	class Sprite
	{
	public:
		Sprite();
		~Sprite();
		void Init(float x, float y, float width, float height, std::string texturePath);
		void Draw();

		//VARIABLES
	private:
		int x;
		int y;
		int width;
		int height;
		GLuint bufferObject;
		Texture texture;
	};
}