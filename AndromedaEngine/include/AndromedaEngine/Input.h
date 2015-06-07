#pragma once
#include <unordered_map>
#include "Vector.h"

namespace AndromedaEngine
{
	class Input
	{
	public:
		//Set the key that was pressed to true via SDL
		static void KeyPressed(int keyID);
		//Set the key that was released to false via SDL
		static void KeyReleased(int keyID);
		//Set the mouse position via SDL
		static void SetMouseCoords(Vector2 position);

		//Returns true when the button passes is pressed
		static bool GetButton(int keyID);
		//Returns mouse position
		static Vector2 GetMousePosition();
	};
}