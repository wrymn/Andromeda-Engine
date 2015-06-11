#pragma once
#include "Component.h"
#include "Vector.h"

namespace AndromedaEngine
{
	class Collider : public Component
	{
	public:
		/*	Whether this collider is only trigger
		- isTrigger[true] = will only check for collision but not collide
		- isTrigger[false] = will check for collision and collide */
		bool isTrigger;
		//Local offset of this collider
		Vector2 offset;

	protected:
		//The type of the collider
		enum ColliderType { CIRCLE, BOX };
		ColliderType colliderType;

	public:
		void Collision(Collider* collider);
		//Circle vs Circle collision detection
		virtual bool CircleVsCircle(Collider* collider);
		//Box vs Box collision detection
		virtual bool BoxVsBox(Collider* collider);
		//Box vs Circle collision detection
		virtual bool BoxVsCircle(Collider* collider);
	};
}