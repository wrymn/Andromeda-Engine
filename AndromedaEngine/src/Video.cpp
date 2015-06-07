#include "Common.h"
#include "Video.h"
#include "Errors.h"
#include "Vector.h"

//--------------------------------------
//            VIDEO OPTIONS

#define DOUBLE_BUFFERING 1
#define FACE_CULLING 0
#define VSYNC 1
#define POLYGON_MODE 0

//--------------------------------------

namespace AndromedaEngine
{
	SDL_Window* Video::SDL_window = NULL;
	int Video::screenWidth = SCREEN_WIDTH;
	int Video::screenHeight = SCREEN_HEIGHT;
	bool Video::fullscreen = false;
	std::string Video::windowTitle = ENGINE_NAME;

	//Initializes game engine video
	void Video::Initialize()
	{
		//Use double buffering for engine
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, DOUBLE_BUFFERING);

		//Initialize game screen
		Create_Window();

		//Enable WireFrame mode
		if (POLYGON_MODE)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	
	//Creates an window
	void Video::Create_Window()
	{
		//Create SDL Window
		SDL_window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_OPENGL);
		Error(SDL_window == nullptr, "SDL Window could not be created!", true);

		//Initialize OpenGL
		SDL_GLContext gl_context = SDL_GL_CreateContext(SDL_window);
		Error(gl_context == nullptr, "SDL context could not be created!", true);

		//Initialize Glew
		GLenum glInitReturn = glewInit();
		Error(glInitReturn != GLEW_OK, "Glew could not be initialized!", true);


		//Set the screen color
		glClearColor(0.4f, 0.4f, 0.4f, 1.0f);

		//Turn off VSYNC
		EnableVSYNC(VSYNC);

		//Set the face culling
		if (FACE_CULLING)
			glEnable(GL_CULL_FACE);

		//Enable Alpha Blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	//Enables/Disables vertical synchronization (VSYNC)
	void Video::EnableVSYNC(const bool& enable)
	{
		SDL_GL_SetSwapInterval(enable);
	}

	//Returns the screen width in pixels
	int Video::GetScreenWidth()
	{
		return screenWidth;
	}

	//Sets whether the game should run in full-screen mode
	void Video::SetFullscreen(const bool& fullscreen)
	{
		Video::fullscreen = fullscreen;

		if (fullscreen)
			SDL_SetWindowFullscreen(SDL_window, SDL_WINDOW_FULLSCREEN);
		else
			SDL_SetWindowFullscreen(SDL_window, 0);
	}

	//Sets the windows fullscreen state
	void Video::SetWindowState(WindowState windowMode)
	{
		switch (windowMode)
		{
			case FULLSCREEN:
				SDL_SetWindowFullscreen(SDL_window, SDL_WINDOW_FULLSCREEN);
				Video::fullscreen = true;
				break;
			case FULLSCREEN_DESKTOP:
				SDL_SetWindowFullscreen(SDL_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
				Video::fullscreen = true;
				break;
		}
	}

	//Sets the window title
	void Video::SetWindowTitle(const std::string& title)
	{
		Video::windowTitle = title;
		SDL_SetWindowTitle(SDL_window, title.c_str());
	}

	//Returns true when the game is in full-screen mode, false if otherwise
	bool Video::IsFullscreen()
	{
		return Video::fullscreen;
	}

	//Returns the screen height in pixels
	int Video::GetScreenHeight()
	{
		return screenHeight;
	}

	//Returns the SDL_Window
	SDL_Window* Video::GetWindow()
	{
		return SDL_window;
	}

	//Returns the SDL_Renderer
	SDL_Renderer* Video::GetRenderer()
	{
		return NULL;
	}

	void Video::SwapBuffer()
	{
		//Swap buffer to render on screen this loop
		SDL_GL_SwapWindow(SDL_window);
	}

	//Set the screen resolution
	void Video::SetResolution(const float& width, const float& height)
	{
		Video::screenWidth = width;
		Video::screenHeight = height;
	}

	//Frees all video resources
	void Video::Quit()
	{
		if (SDL_window != nullptr)
		{
			SDL_DestroyWindow(SDL_window);
			SDL_window = nullptr;
		}
	}
}