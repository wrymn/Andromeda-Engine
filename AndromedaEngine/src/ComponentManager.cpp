#include <iostream>
#include "ComponentManager.h"

namespace AndromedaEngine
{
	ComponentManager::ComponentManager()
	{
		componentIncrement = 1000;
		currentComponentsSize += componentIncrement;
		currentComponentCount = 0;

		ResizeComponents();
	}

	Component* ComponentManager::AddComponent(Component* component)
	{
		//Initialize component itself
		component->Initialize();

		currentComponentCount++;

		//When we reach the vector component limit, resize it
		if (currentComponentCount == currentComponentsSize - 1)
			ResizeComponents();

		//Add to the list of total components
		this->components.push_back(component);

		//---------------------------------------------------------
		//In case component is Collider, add it to collider list
		if (Collider* collider = dynamic_cast<Collider*>(component))
			colliders.push_back(collider);

		//In case component is SpriteRenderer, add it to spriteRenderers list
		if (SpriteRenderer* spriteRenderer = dynamic_cast<SpriteRenderer*>(component))
			spriteRenderers.push_back(spriteRenderer);
		//---------------------------------------------------------

		//Return just added component
		return components.back();
	}

	bool ComponentManager::RemoveComponent(component_vector_const_itr component_itr)
	{
		//---------------------------------------------------------
		//In case component is Collider, remove it from collider list
		if (Collider* collider = dynamic_cast<Collider*>(*component_itr))
			colliders.erase(std::remove(colliders.begin(), colliders.end(), collider), colliders.end());

		//In case component is SpriteRenderer, remove it from spriteRenderers list
		if (SpriteRenderer* spriteRenderer = dynamic_cast<SpriteRenderer*>(*component_itr))
			spriteRenderers.erase(std::remove(spriteRenderers.begin(), spriteRenderers.end(), spriteRenderer), spriteRenderers.end());
		//---------------------------------------------------------

		//Erase the component completely
		this->components.erase(component_itr);

		currentComponentCount--;

		return true;
	}

	//Updates all components on scene, called from the scene ComponentManager is created from
	void ComponentManager::UpdateComponents()
	{
		for (component_vector_itr itr = components.begin(); itr != components.end(); itr++)
		{
			if (*itr != NULL)
			{
				if ((*itr)->isEnabled)
					(*itr)->Update();
			}
		}
	}

	//Updates all Collider components
	void ComponentManager::UpdateColliders()
	{
		//Update collision of Objects which have collider attached
		for (int i = 0; i < colliders.size(); i++)
		{
			for (int j = i + 1; j < colliders.size(); j++)
				colliders[i]->Collision(colliders[j]);
		}
	}

	//Updates all SpriteRenderer components
	void ComponentManager::UpdateSpriteRenderers()
	{
		//Adds SpriteRenderer textures into spriteBatch class for render
		for (int i = 0; i < spriteRenderers.size(); i++)
			spriteRenderers[i]->UpdateSprite();
	}

	void ComponentManager::ResizeComponents()
	{
		//Resizes the entire Vector
		components.resize(currentComponentsSize + componentIncrement);
		currentComponentsSize += componentIncrement;
	}

	void ComponentManager::Clear()
	{
		//Iterate through all components
		for (component_vector_itr itr = components.begin(); itr != components.end(); itr++)
		{
			delete (*itr);
		}
		components.clear();
	}

	ComponentManager::~ComponentManager()
	{
		Clear();
	}
}