#include <iostream>
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Scene.h"

namespace AndromedaEngine{

	SpriteRenderer::SpriteRenderer(){}

	void SpriteRenderer::Initialize()
	{
		isActive = true;
	}

	//////////////////////////////////////////////////////////////////////////////////////

	void SpriteRenderer::Update()
	{
		//If the texture is assigned, draw it
		if (texture.id != 0 && isActive)
		{
			//Set parameters
			glm::vec4 destRect;
			destRect = { gameObject->transform->position.x, gameObject->transform->position.y, gameObject->transform->scale.x, gameObject->transform->scale.y };
			glm::vec4 uvRect;
			uvRect = { 0, 0, 1, 1 };

			//Add and Draw
			gameObject->scene->GetSceneRenderer()->GetSpriteBatch()->AddSprite(destRect, uvRect, texture.id, 0, color);
		}
	}

	SpriteRenderer::~SpriteRenderer(){}
}