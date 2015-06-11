#include <iostream>
#include "Manager.h"
#include "GameObject.h"
#include "Vector.h"
#include "Scene.h"

namespace AndromedaEngine
{
	std::vector<Manager*> Manager::managers;

	Manager::Manager()
	{
		Manager::managers.push_back(this);
	}

	//Destroys passed game object
	void Manager::Destroy(GameObject* object)
	{
		object->scene->RemoveGameObject(object);
	}

	//Creates new game object and adds it to scene
	GameObject* Manager::Instantiate(GameObject* object, Vector2 position)
	{
		//Add transform component to this object, which is required
		object->AddComponent(object->transform);

		//Give the object an position
		object->transform->position = position;

		//Add game object to active scene
		Scene::AddGameObject(object);

		return object;
	}

	Manager::~Manager(){}
	void Manager::Update(){}
}