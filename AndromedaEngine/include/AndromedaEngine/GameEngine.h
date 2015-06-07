#pragma once
#include <Windows.h>
#include <vector>
#include <iostream>
#include <SDL2\SDL.h>
#include "Camera.h"

namespace AndromedaEngine
{
	class GameEngine sealed
	{
	public:
		//Initializes Engine with all its parts
		void EngineInit();
		//Starts the engine and game loop
		void EngineStart();
		

	private:
		//Main
		void ProcessInput();
		void GameLoop();

		void UpdateManagers();
		void UpdateScene();
		void PhysicsUpdate();
		void RenderGame();

		//Utility
		void calculateFPS();
		void limitFPS();

		bool isExiting();

	private:
		//FPS management
		float fps;
		float frameTime;
		float time;

		bool exiting;
	};
}