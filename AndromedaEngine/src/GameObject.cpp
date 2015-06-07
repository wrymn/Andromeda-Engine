#include "GameObject.h"
#include "GameEngine.h"
#include "Scene.h"
#include "Errors.h"

namespace AndromedaEngine
{
	GameObject::GameObject()
	{
		//If there is scene created
		if (Scene::currentScene != NULL)
		{
			this->gameObject = this;
			this->parent = NULL;
			this->transform = NULL;
			this->name = "GameObject";
			this->tag = "";
			this->scene = Scene::currentScene;

			//Catches for error
			HRESULT result = CoCreateGuid(&guid);

			Create();
		}
		else
			Error("Cannot create gameObject without scene", true);
	}

	void GameObject::Create()
	{
		this->transform = new Transform();
		this->transform->gameObject = this->gameObject;
		this->AddComponent(transform);
	}

	void GameObject::Destroy(GameObject* object)
	{
		object->scene->RemoveGameObject(object);
	}

	void GameObject::Destroy()
	{
		//Destroy all gameObject`s children
		for (gameObject_vector_itr itr = children.begin(); itr != children.end(); itr++)
		{
			(*itr)->scene->RemoveGameObject(*itr);
			delete (*itr);
		}

		//Destroy all components attached to this gameObject
		for (component_vector_itr itr = components.begin(); itr != components.end(); itr++)
		{
			this->scene->componentManager->RemoveComponent(itr);
			delete (*itr);
		}

		children.clear();
		components.clear();
	}

	void GameObject::AddComponent(Component* component)
	{
		component->gameObject = this->gameObject;
		components.push_back(component);
		this->scene->componentManager->AddComponent(component);
	}

	template<typename T>
	T* GameObject::FindComponentByType()
	{
		for (component_vector_itr itr = components.begin(); itr != components.end(); itr++)
		{
			//If component is of type, dynamic cast will cast it
			if (T* type = dynamic_cast<T*>(*itr))
			{
				return type;
			}
		}

		return NULL;
	}

	void GameObject::AddChild(GameObject* gameObject)
	{
		gameObject->parent = this;
		gameObject->Create();
		this->children.push_back(gameObject);
	}

	GameObject* GameObject::FindChildByName(std::string const name)
	{
		gameObject_vector_itr itr = std::find_if(children.begin(), children.end(), GameObjectComparer(gameObject->name));
		if (itr != children.end())
			return *itr;
		else
			return NULL;
	}

	/*
	std::vector<GameObject*> GameObject::FindAllChildrenByName(std::string name)
	{
		
	}
	*/

	void GameObject::Start(){}
	void GameObject::Update(){}
	void GameObject::OnCollisionEnter(Collider& collider){}

	GameObject::~GameObject()
	{
		//DELETE ALL POINTERS
	}
}