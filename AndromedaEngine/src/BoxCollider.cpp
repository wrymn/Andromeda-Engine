#include <iostream>
#include "BoxCollider.h"
#include "GameObject.h"
#include "MathA.h"

namespace AndromedaEngine
{
	BoxCollider::BoxCollider()
	{
		//Set default properties
		colliderType = BOX;
		isTrigger = false;
		bounds.width = 1;
		bounds.height = 1;
	}

	//Initializes the component (Called after transform component is initialized)
	void BoxCollider::Initialize()
	{
		
		
	}

	void BoxCollider::Update()
	{
		bounds.x = gameObject->transform->position.x;
		bounds.y = gameObject->transform->position.y;
		bounds.width = gameObject->transform->scale.x;
		bounds.height = gameObject->transform->scale.y;
	}

	//Box vs Box collision detection
	bool BoxCollider::BoxVsBox(Collider* collider)
	{
		//Get and cast other collider
		BoxCollider& otherBoxCollider = dynamic_cast<BoxCollider&>(*collider);

		//Check if colliders collide
		if (!( bounds.y + bounds.height < otherBoxCollider.bounds.y // b1 below b2
			|| otherBoxCollider.bounds.y + otherBoxCollider.bounds.height < bounds.y // b2 below b1
			|| bounds.x + bounds.width < otherBoxCollider.bounds.x // b2 to the right of b1
			|| otherBoxCollider.bounds.x + otherBoxCollider.bounds.width < bounds.x)) // b1 to the right of b2)
		{
			//If this collider is not just an trigger, do collision reponse
			if (!isTrigger)
				CollisionResponse_BoxVsBox(otherBoxCollider);

			//Return that we have a collision
			return true;
		}

		//No collision detected
		return false;
	}

	//Physics Collision reponse
	void BoxCollider::CollisionResponse_BoxVsBox(BoxCollider& otherBoxCollider)
	{
		//top-left
		if (otherBoxCollider.OverlapPoint(Vector2(bounds.x, bounds.y + bounds.height)))
		{
			//Get collision point difference
			float colDiff_x = bounds.x - (otherBoxCollider.bounds.x);
			float colDiff_y = bounds.y - (otherBoxCollider.bounds.y);
			float colDepth_x = bounds.x - (otherBoxCollider.bounds.x + otherBoxCollider.bounds.width);
			float colDepth_y = (bounds.y + bounds.height) - otherBoxCollider.bounds.y;

			colDiff_x = MathA::Abs(colDiff_x);
			colDiff_y = MathA::Abs(colDiff_y);
			colDepth_x = MathA::Abs(colDepth_x);
			colDepth_y = MathA::Abs(colDepth_y);

			//To which axis make collision response
			if (colDiff_x > colDiff_y)
			{
				gameObject->transform->position.x += colDepth_x / 2.0f;
				otherBoxCollider.gameObject->transform->position.x -= colDepth_x / 2.0f;
			}
			else
			{
				gameObject->transform->position.y -= colDepth_y / 2.0f;
				otherBoxCollider.gameObject->transform->position.y += colDepth_y / 2.0f;
			}
		}
		//top-right
		if (otherBoxCollider.OverlapPoint(Vector2(bounds.x + bounds.width, bounds.y + bounds.height)))
		{
			//Get collision point difference
			float colDiff_x = (bounds.x + bounds.width) - (otherBoxCollider.bounds.x + otherBoxCollider.bounds.width);
			float colDiff_y = bounds.y - (otherBoxCollider.bounds.y);
			float colDepth_x = (bounds.x + bounds.width) - otherBoxCollider.bounds.x;
			float colDepth_y = (bounds.y + bounds.height) - otherBoxCollider.bounds.y;

			colDiff_x = MathA::Abs(colDiff_x);
			colDiff_y = MathA::Abs(colDiff_y);
			colDepth_x = MathA::Abs(colDepth_x);
			colDepth_y = MathA::Abs(colDepth_y);

			//To which axis make collision response
			if (colDiff_x > colDiff_y)
			{
				gameObject->transform->position.x -= colDepth_x / 2.0f;
				otherBoxCollider.gameObject->transform->position.x += colDepth_x / 2.0f;
			}
			else
			{
				gameObject->transform->position.y -= colDepth_y / 2.0f;
				otherBoxCollider.gameObject->transform->position.y += colDepth_y / 2.0f;
			}
		}
		//bottom-left
		if (otherBoxCollider.OverlapPoint(Vector2(bounds.x, bounds.y)))
		{
			//Get collision point difference
			float colDiff_x = bounds.x - (otherBoxCollider.bounds.x);
			float colDiff_y = bounds.y - (otherBoxCollider.bounds.y);
			float colDepth_x = bounds.x - (otherBoxCollider.bounds.x + otherBoxCollider.bounds.width);
			float colDepth_y = bounds.y - (otherBoxCollider.bounds.y + otherBoxCollider.bounds.height);

			colDiff_x = MathA::Abs(colDiff_x);
			colDiff_y = MathA::Abs(colDiff_y);
			colDepth_x = MathA::Abs(colDepth_x);
			colDepth_y = MathA::Abs(colDepth_y);

			//To which axis make collision response
			if (colDiff_x > colDiff_y)
			{
				gameObject->transform->position.x += colDepth_x / 2.0f;
				otherBoxCollider.gameObject->transform->position.x -= colDepth_x / 2.0f;
			}
			else
			{
				gameObject->transform->position.y += colDepth_y / 2.0f;
				otherBoxCollider.gameObject->transform->position.y -= colDepth_y / 2.0f;
			}
		}
		//bottom-right
		if (otherBoxCollider.OverlapPoint(Vector2(bounds.x + bounds.width, bounds.y)))
		{
			//Get collision point difference
			float colDiff_x = (bounds.x + bounds.width) - (otherBoxCollider.bounds.x + otherBoxCollider.bounds.width);
			float colDiff_y = bounds.y - (otherBoxCollider.bounds.y);
			float colDepth_x = (bounds.x + bounds.width) - otherBoxCollider.bounds.x;
			float colDepth_y = bounds.y - (otherBoxCollider.bounds.y + otherBoxCollider.bounds.height);

			colDiff_x = MathA::Abs(colDiff_x);
			colDiff_y = MathA::Abs(colDiff_y);
			colDepth_x = MathA::Abs(colDepth_x);
			colDepth_y = MathA::Abs(colDepth_y);

			//To which axis make collision response
			if (colDiff_x > colDiff_y)
			{
				gameObject->transform->position.x -= colDepth_x / 2.0f;
				otherBoxCollider.gameObject->transform->position.x += colDepth_x / 2.0f;
			}
			else
			{
				gameObject->transform->position.y += colDepth_y / 2.0f;
				otherBoxCollider.gameObject->transform->position.y -= colDepth_y / 2.0f;
			}
		}
	}

	//Check if the collider overlaps point in space
	bool BoxCollider::OverlapPoint(Vector2 point) const
	{
		if (point.x >= bounds.x && point.x <= bounds.x + bounds.width && point.y >= bounds.y && point.y <= bounds.y + bounds.height)
			return true;
		else
			return false;
	}

	//Box vs Circle collision detection
	bool BoxCollider::BoxVsCircle(Collider* collider)
	{
		return false;
	}

	BoxCollider::~BoxCollider(){}
}