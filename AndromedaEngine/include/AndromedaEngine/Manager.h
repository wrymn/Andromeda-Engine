#pragma once
#include <vector>

/*
	Manager base class.
	Only classes which do not require active scene inherit from this class.
*/

namespace AndromedaEngine
{
	class GameObject;
	class Vector2;

	class Manager
	{
	protected:
		virtual void Update();
		//Creates a new object and adds it to active scene
		GameObject* Instantiate(GameObject* object, Vector2 position);
		//Destroys an passed gameObject
		void Destroy(GameObject* object);

	private:
		static std::vector<Manager*> managers;
		friend class GameEngine;

	public:
		Manager();
		~Manager();
	};
}