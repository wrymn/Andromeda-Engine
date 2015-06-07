#include "Input.h"

namespace AndromedaEngine
{
	static std::unordered_map<unsigned int, bool> keyMap;
	static Vector2 mouseCoords = { 0, 0 };

	void Input::SetMouseCoords(Vector2 position) { mouseCoords = position; }

	void Input::KeyPressed(int keyID)
	{
		keyMap[keyID] = true;
	}
	void Input::KeyReleased(int keyID)
	{
		keyMap[keyID] = false;
	}

	bool Input::GetButton(int keyID)
	{
		auto it = keyMap.find(keyID);
		if (it != keyMap.end())
			return keyMap[keyID];
		else
			return false;
	}

	Vector2 Input::GetMousePosition()
	{
		return mouseCoords;
	}
}