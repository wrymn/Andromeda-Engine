#pragma once
#include "Component.h"

namespace AndromedaEngine
{
	class Collider : public Component
	{
	public:
		enum ColliderType { CIRCLE, BOX };
		ColliderType colliderType;

	public:
		virtual void Collision(Collider* collider);

	public:
		Collider();
		~Collider();
	};
}