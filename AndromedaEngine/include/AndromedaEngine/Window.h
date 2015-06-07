#pragma once
#include <SDL2\SDL.h>
#include <GL\glew.h>
#include <string>

namespace AndromedaEngine
{
	class GameEngine;

	enum WindowFlags{ INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

	class Window
	{
	public:
		static float width;
		static float height;

	public:
		//Creates an instance of screen Window. If Window already exists, Window is returned
		static Window* MainWindow();
		/*	Creates and returns a Main Window
			- [windowName] = the name of the craeted window
			- [screenWidth] = width of the created window in pixels
			- [screenheight] = height of the created window in pixels
			- [windowFlag] = pass NULL for default value. {INVISIBLE, FULLSCREEN, BORDERLESS} */
		static Window* MainWindow(std::string windowName, int screenWidth, int screenHeight, unsigned int windowFlags);

		//Returns the screen width
		int GetScreenWidth() { return screenWidth; };
		//Returns the screen height
		int GetScreenHeight() { return screenHeight; };

		//Set the screen resolution
		static void SetResolution(float width, float height);

	private:
		//Swap back buffer to front buffer
		void swapBuffer();

		friend class Renderer;
	private:
		//Creates window
		int Create(std::string windowName, int screenWidth, int screenHeight, unsigned int windowFlags);

	private:
		//Main singleton instance of window
		static Window* mainWindow;
		SDL_Window *window;
		int screenWidth;
		int screenHeight;

	private:
		Window(std::string windowName, int screenWidth, int screenHeight, unsigned int windowFlags);
		~Window();

		friend class GameEngine;
	};
}
