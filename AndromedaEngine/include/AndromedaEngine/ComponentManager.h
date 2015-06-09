#pragma once
#include <vector>
#include "Collider.h"
#include "GameObject.h"
#include "Renderer.h"
#include "SpriteRenderer.h"

namespace AndromedaEngine
{

	class ComponentManager
	{
	public:
		typedef std::vector<Component*> component_vector;
		typedef component_vector::iterator component_vector_itr;
		typedef component_vector::const_iterator component_vector_const_itr;

		//List of all components available in scene
		component_vector components;
		
		//Adds components to the slist
		Component* AddComponent(Component* component);
		//Removes an component from the list
		bool RemoveComponent(component_vector_const_itr component_itr);

		ComponentManager();
		~ComponentManager();

	private:
		//List of all colliders in component manager
		std::vector<Collider*> colliders;
		//List of all colliders in component manager
		std::vector<SpriteRenderer*> spriteRenderers;

		//Size we increment component Vector when it reaches the limit
		int componentIncrement;
		//The maximum limit of component Vector before resizing
		int currentComponentsSize;
		//Current number of components in the Vector
		int currentComponentCount;

	private:
		//Clears all components from ComponentManager
		void Clear();
		//Updates all components on scene, called from the scene ComponentManager is created from
		void UpdateComponents();
		//Updates all Collider components
		void UpdateColliders();
		//Updates all SpriteRenderer components
		void UpdateSpriteRenderers();

		//Resizes the component vector when it reaches its limit
		void ResizeComponents();

		friend class Scene;
	};
}