#include "Scene.h"
#include "CircleCollider2D.h"
#include <iostream>

namespace AndromedaEngine
{
	std::vector<Scene*> Scene::scenes;
	Scene* Scene::currentScene = NULL;

	Scene::Scene()
	{
		//If this is the first scene created, make it the current scene
		if(Scene::currentScene == NULL)
			Scene::currentScene = this;

		//Initialize
		componentManager = new ComponentManager();
		renderer = new Renderer(*this);
		isActive = false;
		scenes.push_back(this);
		SetInitialName();

		std::cout << "New scene \"" << this->name << "\" was created" << std::endl;
	}

	void Scene::SetInitialName()
	{
		//If there are more scenes, set incremental name
		if (Scene::scenes.size() > 1)
		{
			name = "Scene " + Scene::scenes.size();
			return;
		}
		//If this is the first scene, set it`s name
		name = "Scene";
	}

	void Scene::Update()
	{
		//Call Update() method for all GameObjects
		for (int i = 0; i < gameObjects.size(); i++)
		{
			gameObjects[i]->Update();
		}
		//Update componentManager and all components on scene
		componentManager->UpdateComponents();
	}

	void Scene::UpdateScenePhysics()
	{
		componentManager->UpdateColliders();
	}

	void Scene::UpdateSpriteRenderers()
	{
		componentManager->UpdateSpriteRenderers();
	}

	void Scene::Render()
	{
		renderer->Render();
	}

	void Scene::AddGameObject(GameObject* object)
	{
		Scene::currentScene->gameObjects.push_back(object);
	}

	Scene* Scene::GetCurrentScene()
	{
		return Scene::currentScene;
	}

	void Scene::RemoveGameObject(GameObject* object)
	{
		for (gameObject_vector_itr itr = Scene::currentScene->gameObjects.begin(); itr < Scene::currentScene->gameObjects.end(); itr++)
		{
			if ((*itr) == object)
			{
				(*itr)->DestroyThisObject();
				Scene::currentScene->gameObjects.erase(itr);
				delete *itr;
				break;
			}
		}
	}

	bool Scene::RemoveScene()
	{
		//Check if this is not the current scene
		if (currentScene == this)
			return false;

		//Remove all objects from scene
		for (gameObject_vector_itr itr = gameObjects.begin(); itr < gameObjects.end(); itr++)
		{
			gameObjects.erase(itr);
			delete *itr;
		}

		delete componentManager;
		return true;
	}

	void Scene::SetActive()
	{
		//Deactivate all other scenes
		for (std::vector<Scene*>::iterator itr = scenes.begin(); itr != scenes.end(); itr++)
			(*itr)->isActive = false;

		//Activate this scene
		isActive = true;

		//Set this active scene as currentScene
		currentScene = this;
	}

	bool Scene::IsSceneActive()
	{
		return isActive;
	}

	Renderer* Scene::GetSceneRenderer()
	{
		return renderer;
	}

	Scene::~Scene()
	{
		RemoveScene();
	}
}