#pragma once
#include <GL\glew.h>

namespace AndromedaEngine
{
	/*	Color consists of Red, Green, Blue, Alpha values
		- min value is 0, max value is 255 */
	struct Color{
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;

		//Creates RGBA Color 0 - 255
		Color(GLubyte r, GLubyte g, GLubyte b, GLubyte a) : r(r), g(g), b(b), a(a) {}
		//Creates RGB Color 0 - 255
		//Default A is 255
		Color(GLubyte r, GLubyte g, GLubyte b) : r(r), g(g), b(b), a(255) {}
		//Creates default RGBA Color
		//Default RGBA is 255
		Color() : r(255), g(255), b(255), a(255) {}
	};
}