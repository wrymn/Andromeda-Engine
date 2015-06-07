#pragma once
#include <vector>

/*
	Manager base class.
	Only classes which do not require active scene inherit from this class.
*/

namespace AndromedaEngine
{
	class Manager
	{
	protected:
		virtual void Update();

	private:
		static std::vector<Manager*> managers;
		friend class GameEngine;

	public:
		Manager();
		~Manager();
	};
}