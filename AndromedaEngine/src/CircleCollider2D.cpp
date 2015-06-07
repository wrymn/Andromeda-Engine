#include "CircleCollider2D.h"
#include "GameEngine.h"
#include "GameObject.h"

namespace AndromedaEngine
{
	CircleCollider2D::CircleCollider2D(){}

	void CircleCollider2D::Initialize()
	{
		GetTransformScale();
		radius = 1;
		isActive = true;
		isTrigger = false;
		colliderType = CIRCLE;
	}

	void CircleCollider2D::GetTransformScale()
	{
		transformScale = gameObject->transform->scale.x;
		if (gameObject->transform->scale.y > transformScale)
			transformScale = gameObject->transform->scale.y;
	}

	void CircleCollider2D::Collision(Collider* collider)
	{
		if (isActive)
		{
			//Set the transform scale of this Collider first
			GetTransformScale();

			//Circle vs Circle collision
			if (colliderType == CIRCLE && collider->colliderType == CIRCLE)
				CircleVsCircle(collider);
		}
	}

	void CircleCollider2D::CircleVsCircle(Collider* collider)
	{
		//Get CircleCollider2D
		CircleCollider2D* circleCollider = dynamic_cast<CircleCollider2D*>(collider);

		//Get transform scale for colliding collider
		float otherCollisionTransformScale = circleCollider->gameObject->transform->scale.x > circleCollider->gameObject->transform->scale.y ? circleCollider->gameObject->transform->scale.x : circleCollider->gameObject->transform->scale.y;

		//If collision detection is Enabled
		if (isActive)
		{
			float radiusA = (transformScale * radius) / 2;
			float radiusB = (otherCollisionTransformScale * circleCollider->radius) / 2;

			float minDistance = radiusA + radiusB;

			// 1. Get center position of GameObject
			Vector2 centerPosA = gameObject->transform->position + radiusA;
			Vector2 centerPosB = circleCollider->gameObject->transform->position + radiusB;

			// 2. Get distance between them
			Vector2 vecDistance = centerPosA - centerPosB;
			float distance = vecDistance.Magnitude();

			// 4. If the Length is smaller than minimum distance, we have a collision
			float collisionDepth = minDistance - distance;

			// 5. We have a collision
			if (collisionDepth > 0)
			{
				//Call collision enter function
				gameObject->OnCollisionEnter(*collider);

				//If we should also do collision reponse
				if (!isTrigger)
				{
					//Perform position change due to collision
					gameObject->transform->position += (vecDistance.Normalize() * collisionDepth) / 2;
					circleCollider->gameObject->transform->position -= (vecDistance.Normalize() * collisionDepth) / 2;
				}
			}
		}
	}

	CircleCollider2D::~CircleCollider2D(){}
}