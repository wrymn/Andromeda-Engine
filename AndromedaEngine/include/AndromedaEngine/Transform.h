#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <glm\gtc\quaternion.hpp>

#include "Vector.h"
#include "Component.h"

namespace AndromedaEngine
{
	class GameObject;

	class Transform : public Component
	{
	public:
		//Position of this gameObject
		Vector2 position;
		//Position of this gameObject relative to it`s parent
		Vector2 localPosition;
		//Scale of this gameObject
		Vector2 scale;
		//Rotation of this gameObject
		glm::quat rotation;
		//Direction of this GameObject
		Vector2 direction;
		//Position of gameObject in world, not relative to it`s parent
		Vector2 worldPosition;

	public:
		//Translates the object in given direction
		void Translate(Vector2 translation);
		//Translates the object by amount in it`s direction
		void Translate(float amount);
		//Rotates the object by given angle *NOT IMPLEMETED*
		Transform* Rotate(Vector2 axis, float angle);

	private:
		void Update();
		//Initializes the component
		void Initialize();

	public:
		Transform();
		~Transform();
	};
}
#endif