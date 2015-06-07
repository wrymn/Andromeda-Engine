#include "GameEngine.h"
#include "Scene.h"
#include "Input.h"
#include "Time.h"

#include "Window.h"
#include "Manager.h"

namespace AndromedaEngine
{

	//Runs the Engine from the program start
	void GameEngine::Run()
	{
		EngineInit();
		GameLoop();
	}

	//Starts the Game Engine and main loop
	void GameEngine::EngineStart()
	{
		GameLoop();
	}

	//Initializes Engine with all it`s components
	void GameEngine::EngineInit()
	{
		engineState = EngineState::RUNNING;
		//Initialize SDL
		SDL_Init(SDL_INIT_EVERYTHING);
		//Use double buffering for engine
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		//Initialize game screen
		Window::MainWindow("Andromeda Engine", 1024, 768, NULL);
		//Initialize main camera
		mainCamera.Init(Window::width, Window::height);
		Camera::mainCamera = &mainCamera;
		
		//Lock the game FPS
		//Time::LockFPS(30);

		//Enable WireFrame mode
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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
				engineState = EngineState::EXIT;
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
		while (engineState != EngineState::EXIT)
		{
			Time::Begin();

			calculateFPS();
			ProcessInput();
			mainCamera.Update();

			UpdateManagers();
			UpdateScene();
			PhysicsUpdate();
			RenderGame();

			limitFPS();
			Time::End();
		}
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
