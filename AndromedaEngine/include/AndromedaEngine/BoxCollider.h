#pragma once
#include "Collider.h"
#include "Vector.h"

namespace AndromedaEngine
{
	class BoxCollider : public Collider
	{
	public:
		Rect bounds;

	public:
		//Check if the collider overlaps point in space
		bool OverlapPoint(Vector2 point) const;

	private:
		//Initializes the component
		void Initialize() override;
		//Box vs Box collision detection
		bool BoxVsBox(Collider* collider) override;
		//Box vs Circle collision detection
		bool BoxVsCircle(Collider* collider) override;

		//Updates this collider
		void Update() override;
		//Physics Collision reponse
		void CollisionResponse_BoxVsBox(BoxCollider& otherBoxCollider);
	public:
		BoxCollider();
		~BoxCollider();
	};
}