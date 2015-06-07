#include "Window.h"
#include "Errors.h"
#include "GLSL_ShaderProgram.h"

namespace AndromedaEngine
{
	Window* Window::mainWindow = NULL;
	float Window::width = 680;
	float Window::height = 450;

	Window::Window(std::string windowName, int screenWidth, int screenHeight, unsigned int windowFlags)
	{
		Create(windowName, screenWidth, screenHeight, windowFlags);
	}

	Window::~Window(){}

	Window* Window::MainWindow()
	{
		//In case main window is not created, create window with default values
		if (mainWindow == NULL)
			mainWindow = new Window("Andromeda Engine", 640, 480, NULL);

		return Window::mainWindow;
	}

	Window* Window::MainWindow(std::string windowName, int screenWidth, int screenHeight, unsigned int windowFlags)
	{
		if (mainWindow == NULL)
			mainWindow = new Window(windowName, screenWidth, screenHeight, windowFlags);

		return Window::mainWindow;
	}

	int Window::Create(std::string windowName, int screenWidth, int screenHeight, unsigned int windowFlags)
	{
		Uint32 flags = SDL_WINDOW_OPENGL;
		if (windowFlags & INVISIBLE)
			flags |= SDL_WINDOW_HIDDEN;
		if (windowFlags & FULLSCREEN)
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		if (windowFlags & BORDERLESS)
			flags |= SDL_WINDOW_BORDERLESS;

		Window::width = screenWidth;
		Window::height = screenHeight;

		//Create SDL Window
		window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Window::width, Window::height, flags);
		Error(window == nullptr, "SDL Window could not be created!", true);

		//Initialize OpenGL
		SDL_GLContext gl_context = SDL_GL_CreateContext(window);
		Error(gl_context == nullptr, "SDL context could not be created!", true);

		//Initialize Glew
		GLenum glInitReturn = glewInit();
		Error(glInitReturn != GLEW_OK, "Glew could not be initialized!", true);


		//Set the screen color
		glClearColor(0.4f, 0.4f, 0.4f, 1.0f);

		//Turn off VSYNC
		SDL_GL_SetSwapInterval(0);

		//Enable Alpha Blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return 0;
	}

	void Window::SetResolution(float width, float height)
	{
		Window::width = width;
		Window::height = height;
	}

	void Window::swapBuffer()
	{
		//Swap buffer to render on screen this loop
		SDL_GL_SwapWindow(window);
	}
}