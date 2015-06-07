#include "MathA.h"

namespace AndromedaEngine
{
	const float MathA::PI = 3.14159265359f;

	float MathA::Deg2Rad(float& angle)
	{ 
		return angle * (MathA::PI / 180);
	};

	float MathA::Rad2Deg(float& radians)
	{ 
		return radians * (180 / MathA::PI);
	};

	template<typename T>
	static T Clamp(T min, T value, T max)
	{
		if (value < min)
			return min;
		else if (value > max)
			return max;
		else
			return value;
	}

	static float Lerp(float start, float end, float t)
	{
		return ((1.0f - t) * start) + (t * end);
	}
}