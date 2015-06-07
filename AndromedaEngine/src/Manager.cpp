#include "Manager.h"

namespace AndromedaEngine
{
	std::vector<Manager*> Manager::managers;

	Manager::Manager()
	{
		Manager::managers.push_back(this);
	}

	Manager::~Manager(){}
	void Manager::Update(){}
}