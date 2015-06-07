#pragma once
#include <SDL2\SDL.h>
#include <GL\glew.h>
#include <string>

namespace AndromedaEngine
{
	enum WindowState { FULLSCREEN, FULLSCREEN_DESKTOP };

	class Renderer;

	class Video
	{
	public:
		//Initializes game engine video
		static void Initialize();
		//Frees all video resources
		static void Quit();

		//Returns the screen width in pixels
		static int GetScreenWidth();
		//Returns the screen height in pixels
		static int GetScreenHeight();
		//Returns the SDL_Window
		static SDL_Window* GetWindow();
		//Returns the SDL_Renderer
		static SDL_Renderer* GetRenderer();
		//Returns true when the game is in full-screen mode, false if otherwise
		static bool IsFullscreen();

		//Set the screen resolution
		static void SetResolution(const float& width, const float& height);
		/*	Enables/Disables vertical synchronization (VSYNC)
			- synchronizes game with screen refresh rate. Will avoid screen tearing. */
		static void EnableVSYNC(const bool& enable);
		//Sets whether the game should run in full-screen mode
		static void SetFullscreen(const bool& fullscreen);
		/*	Sets the windows fullscreen state
			- WindowMode[FULLSCREEN] = real fullscreen mode
			- WindowMode[FULLSCREEN_DESKTOP] = fake fullscreen with size of the desktop */
		static void SetWindowState(WindowState windowMode);
		//Sets the window title
		static void SetWindowTitle(const std::string& title);

	private:
		//Creates an window
		static void Create_Window();
		//Swap back buffer to front buffer
		static void SwapBuffer();

		friend class Renderer;
	private:
		static SDL_Window *SDL_window;
		static int screenWidth;
		static int screenHeight;
		static bool fullscreen;
		static std::string windowTitle;
	};
}