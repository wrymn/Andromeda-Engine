#include <SDL2\SDL.h>
#include <GL\glew.h>
#include <iostream>
#include "Common.h"
#include "System.h"
#include "Video.h"
#include "Camera.h"

namespace AndromedaEngine
{
	//Initializes Andromeda Engine
	void System::Initialize(int argc, char* argv[])
	{
		//Initialize SDL
		SDL_Init(SDL_INIT_EVERYTHING);

		//Initialize game window
		Video::Initialize();

		//Initialize and create main camera
		Camera::mainCamera = Camera::CreateCamera();

		DisplayInfo();
	}

	void System::DisplayInfo()
	{
		//Get engine name, engine build version
		std::cout << ENGINE_NAME << " " << ANDROMEDA_VERSION << " " << BIT_BUILD << std::endl;
		//Get openGL version
		std::cout << "OpenGL version " << glGetString(GL_VERSION) << std::endl;

		std::cout << std::endl;

		std::cout << "Debug mode: " << DEBUG_MODE << std::endl;

		std::cout << std::endl << std::endl << "-------------------------------" << std::endl << std::endl;
	}

	//Initializes Andromeda Engine
	void System::Quit()
	{
		Video::Quit();
	}
}