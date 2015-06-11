#include <iostream>
#include "Collider.h"
#include "GameObject.h"

namespace AndromedaEngine
{
	void Collider::Collision(Collider* collider)
	{
		if (isEnabled)
		{
			//Circle vs Circle collision
			if (colliderType == CIRCLE && collider->colliderType == CIRCLE)
			{
				if (CircleVsCircle(collider))
				{
					collider->gameObject->OnCollisionEnter(*this);
					this->gameObject->OnCollisionEnter(*collider);
				}
			}
			//Box vs Box collision
			if (colliderType == BOX && collider->colliderType == BOX)
			{
				//If there is collision, called OnCollisionEnter()
				if (BoxVsBox(collider))
				{
					collider->gameObject->OnCollisionEnter(*this);
					this->gameObject->OnCollisionEnter(*collider);
				}
			}
			//Box vs Circle collision
			if ((colliderType == BOX && collider->colliderType == CIRCLE) || (colliderType == CIRCLE && collider->colliderType == BOX))
			{
				if (BoxVsCircle(collider))
				{
					collider->gameObject->OnCollisionEnter(*this);
					this->gameObject->OnCollisionEnter(*collider);
				}
			}
		}
	}

	bool Collider::CircleVsCircle(Collider* collider){ return false; }
	bool Collider::BoxVsBox(Collider* collider){ return false; }
	bool Collider::BoxVsCircle(Collider* collider){ return false; }
}