#include "CircleCollider2D.h"
#include "GameEngine.h"
#include "GameObject.h"

namespace AndromedaEngine
{
	CircleCollider2D::CircleCollider2D()
	{
		//Set default properties
		colliderType = CIRCLE;
		isTrigger = false;
		radius = 1;
	}

	void CircleCollider2D::Initialize()
	{
		GetTransformScale();
	}

	void CircleCollider2D::GetTransformScale()
	{
		maxRadius = gameObject->transform->scale.x;
		if (gameObject->transform->scale.y > maxRadius)
			maxRadius = gameObject->transform->scale.y;
	}

	bool CircleCollider2D::CircleVsCircle(Collider* collider)
	{
		//Set the transform scale of this Collider first
		GetTransformScale();

		//Get CircleCollider2D
		CircleCollider2D* otherCircleCollider = dynamic_cast<CircleCollider2D*>(collider);

		//Get transform scale for colliding collider
		float otherCollisionTransformScale = otherCircleCollider->gameObject->transform->scale.x > otherCircleCollider->gameObject->transform->scale.y ? otherCircleCollider->gameObject->transform->scale.x : otherCircleCollider->gameObject->transform->scale.y;

		float radiusA = (maxRadius * radius) / 2;
		float radiusB = (otherCollisionTransformScale * otherCircleCollider->radius) / 2;

		float minDistance = radiusA + radiusB;

		// 1. Get center position of GameObject
		Vector2 centerPosA = gameObject->transform->position + radiusA;
		Vector2 centerPosB = otherCircleCollider->gameObject->transform->position + radiusB;

		// 2. Get distance between them
		Vector2 vecDistance = centerPosA - centerPosB;
		float distance = vecDistance.Magnitude();

		// 4. If the Length is smaller than minimum distance, we have a collision
		float collisionDepth = minDistance - distance;

		// 5. We have a collision
		if (collisionDepth > 0)
		{
			//If we should also do collision reponse
			if (!isTrigger)
			{
				//Perform position change due to collision
				gameObject->transform->position += (vecDistance.Normalize() * collisionDepth) / 2;
				otherCircleCollider->gameObject->transform->position -= (vecDistance.Normalize() * collisionDepth) / 2;
			}

			//Return that we have a collision
			return true;
		}

		//No collision detected
		return false;
	}

	bool CircleCollider2D::BoxVsCircle(Collider* collider)
	{
		return false;
	}

	CircleCollider2D::~CircleCollider2D(){}
}