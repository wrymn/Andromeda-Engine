#pragma once
#include <string>
#include <algorithm>
#include <typeinfo>
#include <vector>
#include <unordered_map>
#include <memory>
#include <objbase.h>
#include <guiddef.h>

#include "Component.h"
#include "Collider.h"
#include "Transform.h"
#include "ComponentManager.h"

namespace AndromedaEngine
{
	class Scene;

	class GameObject
	{
	public:
		//GameObject reference of this object
		GameObject* gameObject;
		//Parent of this object
		GameObject* parent;
		//Transform component of this object
		Transform* transform;
		//Scene instance this object is in
		Scene* scene;

		//Name of the object
		std::string name;
		//GameObject`s tag
		std::string tag;

		//This gets random-unique string for comparing object`s by name
		GUID guid;
		
		//Add the component to this object
		void AddComponent(Component* component);
		//Finds and return an component by type
		template<typename T>
		T* FindComponentByType();

		//Attaches other objects as children to this one
		void AddChild(GameObject* gameObject);
		//Finds and returns first object by name
		GameObject* FindChildByName(std::string const name);
		//Finds and returns vector of objects by name
		//std::vector<GameObject*> FindAllChildrenByName(std::string name);
		

	protected:
		//Called once at the creation of GameObject
		virtual void Start();
		//Called each frame
		virtual void Update();
		//Called when there is another collision from CircleCollider2D
		virtual void OnCollisionEnter(Collider& collider);

		friend class CircleCollider2D;
		friend class Scene;

	protected:
		//Creates a new object and adds it to active scene
		GameObject* Instantiate(GameObject* object, Vector2 position);
		//Destroys an passed gameObject
		void Destroy(GameObject* object);

	private:
		//Called when object is destroyed
		void DestroyThisObject();

		typedef std::vector<Component*> component_vector;
		typedef component_vector::iterator component_vector_itr;
		typedef component_vector::const_iterator component_vector_const_itr;

		typedef std::vector<GameObject*> gameObject_vector;
		typedef gameObject_vector::iterator gameObject_vector_itr;
		typedef gameObject_vector::const_iterator gameObject_vector_const_itr;

		component_vector components;
		gameObject_vector children;

		friend class Scene;

	public:
		GameObject();
		~GameObject();
	};

	struct GameObjectComparer
	{
		std::string name;

		GameObjectComparer(std::string name) : name(name) {}

		bool operator()(GameObject* object)
		{
			return (object->name == name ? true : false);
		}
	};
}