#pragma once
#include <GL\glew.h>
#include "Vector.h"
#include "Color.h"

namespace AndromedaEngine
{
	struct UV{
		float u;
		float v;

		UV(float u, float v) : u(u), v(v) {};
	};


	struct Vertex{
		Vector2 position{ 0, 0 };
		Color color{ 0, 0, 0, 0 };
		UV uv{ 0, 0 };
	};
}