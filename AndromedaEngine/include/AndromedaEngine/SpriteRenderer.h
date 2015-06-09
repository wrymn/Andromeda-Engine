#pragma once
#include "SpriteBatch.h"
#include "Color.h"
#include "Texture.h"
#include "Component.h"

namespace AndromedaEngine{

	class SpriteRenderer : public Component
	{
	public:
		//Texture of Sprite
		Texture texture;
		//Color of texture;
		Color color;
		//Whether the SpriteRenderer component is active
		bool isActive;

	private:
		//Called to update sprite
		void UpdateSprite();
		//Initializes the component
		void Initialize();

		friend class ComponentManager;

	public:
		SpriteRenderer();
		~SpriteRenderer();
	};
}