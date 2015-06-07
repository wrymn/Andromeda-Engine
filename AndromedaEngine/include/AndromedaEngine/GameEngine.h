#pragma once
#include <Windows.h>
#include <vector>
#include <iostream>

#include "Camera.h"




namespace AndromedaEngine
{
	enum class EngineState { RUNNING, EXIT };

	class GameEngine sealed
	{
	public:
		//Main Run function which has to be called to start the Andromeda Engine
		void Run();
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

	private:
		Camera mainCamera;
		EngineState engineState;

	private:
		//FPS management
		float fps;
		float frameTime;
		float time;
	};
}