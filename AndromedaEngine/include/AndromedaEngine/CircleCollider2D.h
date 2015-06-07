#pragma once
#include "Collider.h"

namespace AndromedaEngine
{
	class CircleCollider2D : public Collider
	{
	public:
		/*	Sets the radius of CircleCollider2D
			- default value is 1 */
		float radius;
		//Whether the CircleCollider2D component is active
		bool isActive;
		/*	Whether this collider is only trigger
			- isTrigger[true] = will only check for collision but not collide
			- isTrigger[false] = will check for collision and collide */
		bool isTrigger;

	private:
		//The base value of radius.
		float transformScale;

	private:
		//Initializes the component
		void Initialize();
		//Override method of collision, called from the scene
		void Collision(Collider* collider);
		//Circle vs Circle collision detection
		void CircleVsCircle(Collider* collider);

		//Sets the base transform scale of CircleCollider2D
		void GetTransformScale();

	public:
		CircleCollider2D();
		~CircleCollider2D();
	};
}