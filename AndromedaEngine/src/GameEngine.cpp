#include "GameEngine.h"
#include "Scene.h"
#include "Input.h"
#include "Time.h"
#include "Manager.h"
#include "Common.h"
#include "Video.h"
#include "System.h"

namespace AndromedaEngine
{
	//Starts the Game Engine and main loop
	void GameEngine::EngineStart()
	{
		GameLoop();
	}

	bool GameEngine::isExiting()
	{
		return exiting;
	}

	//Processes Input
	void GameEngine::ProcessInput()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				exiting = true;
				break;
			case SDL_KEYDOWN:
				Input::KeyPressed(event.key.keysym.sym);
				break;
			case SDL_KEYUP:
				Input::KeyReleased(event.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				Input::KeyPressed(event.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				Input::KeyReleased(event.button.button);
				break;
			case SDL_MOUSEMOTION:
				Input::SetMouseCoords(Vector2(event.motion.x, event.motion.y));
				break;
			}
		}
	}

	//Main game loop
	void GameEngine::GameLoop()
	{
		while (!isExiting())
		{
			Time::Begin();

			calculateFPS();
			ProcessInput();
			Camera::mainCamera->Update();

			UpdateManagers();
			UpdateScene();
			PhysicsUpdate();
			RenderGame();

			limitFPS();
			Time::End();
		}

		if (isExiting())
			System::Quit();
	}

	//Updates all manager base classes
	void GameEngine::UpdateManagers()
	{
		for (std::vector<Manager*>::iterator itr = Manager::managers.begin(); itr != Manager::managers.end(); itr++)
		{
			(*itr)->Update();
		}
	}

	//Update all scenes, gameobjects, component, calls Update() functions...
	void GameEngine::UpdateScene()
	{
		if (Scene::currentScene != NULL)
			Scene::currentScene->Update();
	}

	//Updates the game physics
	void GameEngine::PhysicsUpdate()
	{
		if (Scene::currentScene != NULL)
			Scene::currentScene->UpdateScenePhysics();
	}

	//Render the game to the screen
	void GameEngine::RenderGame()
	{
		if (Scene::currentScene != NULL)
			Scene::currentScene->Render();
	}

	//////////////////////////////////////////////////////////////////////////////////////////
	//Calculate engine FPS
	void GameEngine::calculateFPS()
	{
		time += Time::deltaTime;
		if (time >= 1.5f)
		{
			std::cout << Time::FPS << " FPS  (" << Time::deltaTime * 1000 << "ms)" << std::endl;
			time = 0;
		}
	}

	//Limit game FPS
	void GameEngine::limitFPS()
	{
		if (1000.0f / Time::GetMaxFPS() > (Time::deltaTime * 1000.0f))
		{
			SDL_Delay((Uint32)(1000.0f / Time::GetMaxFPS() - (Time::deltaTime * 1000.0f)));
		}
	}
}
