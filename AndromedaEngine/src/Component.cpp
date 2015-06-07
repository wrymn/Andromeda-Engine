#include "Component.h"
#include "GameObject.h"

namespace AndromedaEngine
{
	Component::Component()
	{
		this->isEnabled = true;
		this->gameObject = NULL;
	}

	//////////////////////////////////////////////////////////////////////////////////////

	void Component::Update(){}
	Component::~Component(){}
}