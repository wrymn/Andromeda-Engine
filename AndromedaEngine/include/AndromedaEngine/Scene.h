#pragma once
#include <string>
#include <vector>
#include "GameObject.h"

#include "Renderer.h"

namespace AndromedaEngine
{
	class Scene
	{
	public:
		typedef std::vector<GameObject*> gameObject_vector;
		typedef gameObject_vector::iterator gameObject_vector_itr;
		typedef gameObject_vector::const_iterator gameObject_vector_const_itr;

		//List of all objects currently in scene
		gameObject_vector gameObjects;
		//Component Manager responsible for updating all components
		ComponentManager *componentManager;
		//The name of the current scene
		std::string name;

	public:
		//List of all existing scenes in the game
		static std::vector<Scene*> scenes;
		

	private:
		//Whether the level is currently active or not
		bool isActive;
		//The renderer instance which renders this entire scene
		Renderer* renderer;
		//Current active scene
		static Scene* currentScene;
		friend class GameEngine;

	public:
		/*	Updates the entire scene
			- calls Update() on all object currently in this scene*/
		void Update();
		//Updates physics and collision of the current scene
		void UpdateScenePhysics();
		//Renders the current scene
		void Render();
		//Returns whether the scene is active or not
		bool IsSceneActive();
		//Activates the scene and deactivates all other scenes
		void SetActive();
		//Returns the current scene renderer
		Renderer* GetSceneRenderer();

	private:
		//Adds an object to this scene
		void AddGameObject(GameObject* object);
		//Removes an object from this scene
		void RemoveGameObject(GameObject* object);
		
		/*	Destroys everything in this scenes and cleans it up
			- If the scene is currentScene, scene won`t be destroyed*/
		bool RemoveScene();
		//Set initial scene name
		void SetInitialName();

		friend class GameObject;
		friend class GameEngine;

	public:
		Scene();
		~Scene();
	};
}