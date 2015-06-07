#include "Transform.h"

namespace AndromedaEngine
{
	Transform::Transform(){}

	void Transform::Initialize()
	{
		this->position = Vector2(0, 0);
		this->scale = Vector2(1, 1);
		this->rotation = glm::quat(1, 0, 0, 0);
		this->direction = Vector2(0, 0);
	}

	//////////////////////////////////////////////////////////////////////////////////////

	void Transform::Translate(Vector2 translation)
	{
		position += translation;
	}

	void Transform::Translate(float amount)
	{
		position += direction * amount;
	}

	Transform* Transform::Rotate(Vector2 axis, float angle)
	{
		//*NOT IMPLEMETED*
		return this;
	}

	void Transform::Update(){}

	Transform::~Transform(){}
}