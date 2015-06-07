#ifndef COMPONENT_H
#define COMPONENT_H
#include <string>
#include <objbase.h>
#include <guiddef.h>

namespace AndromedaEngine
{
	class GameObject;

	class Component
	{
	public:
		//Object pointer this component is attached to
		GameObject *gameObject;
		//Whether the component is active or not
		bool isEnabled;


		Component();
		virtual ~Component();

	protected:
		virtual void Update();
		//Initializes gameObject, called by ComponentManager when component is added to gameObject
		virtual void Initialize() = 0;
		friend class ComponentManager;
	};
}
#endif