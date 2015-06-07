#include <SDL2\SDL.h>
#include <GL\glew.h>
#include "GameEngine.h"
 
namespace AndromedaEngine
{
	GameEngine gameEngine;

	//Initializes Andromeda Engine, this has to be the first which is done
	void InitializeEngine()
	{
		gameEngine.EngineInit();
	}

	//Start Andromeda Engine, step after calling internal game classes
	void StartEngine()
	{
		gameEngine.EngineStart();
	}
}