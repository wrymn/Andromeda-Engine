#include <SDL2\SDL.h>
#include <GL\glew.h>
#include "GameEngine.h"
#include "System.h"

namespace AndromedaEngine
{
	GameEngine gameEngine;

	//Initializes Andromeda Engine, this has to be the first which is done
	void InitializeEngine(int argc, char* argv[])
	{
		System::Initialize(argc, argv);
	}

	//Start Andromeda Engine, step after calling internal game classes
	void StartEngine()
	{
		gameEngine.EngineStart();
	}
}