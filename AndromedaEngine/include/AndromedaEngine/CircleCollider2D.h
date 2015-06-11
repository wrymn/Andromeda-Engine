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
		
	private:
		//The base value of radius.
		float maxRadius;

	private:
		//Initializes the component
		void Initialize() override;
		//Box vs Circle collision detection
		bool CircleVsCircle(Collider* collider) override;
		//Circle vs Circle collision detection
		bool BoxVsCircle(Collider* collider) override;

		//Sets the base transform scale of CircleCollider2D
		void GetTransformScale();

	public:
		CircleCollider2D();
		~CircleCollider2D();
	};
}