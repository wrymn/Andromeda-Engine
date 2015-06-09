#include <iostream>
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Scene.h"

namespace AndromedaEngine{

	SpriteRenderer::SpriteRenderer(){}

	void SpriteRenderer::Initialize()
	{
		color = { 255, 255, 255, 255 };
		isActive = true;
	}

	//////////////////////////////////////////////////////////////////////////////////////

	void SpriteRenderer::UpdateSprite()
	{
		//If the texture is assigned, draw it
		if (texture.id != 0 && isActive)
		{
			//Set parameters
			glm::vec4 destRect;
			destRect = { gameObject->transform->position.x, gameObject->transform->position.y, gameObject->transform->scale.x, gameObject->transform->scale.y };
			glm::vec4 uvRect;
			uvRect = { 0, 0, 1, 1 };

			if (gameObject->name == "0Player")
				std::cout << "Player size: " << gameObject->transform->scale.x << std::endl;

			//Add texture to sprite batch
			gameObject->scene->GetSceneRenderer()->GetSpriteBatch()->AddSprite(destRect, uvRect, texture.id, 0, color);
		}
	}

	SpriteRenderer::~SpriteRenderer(){}
}