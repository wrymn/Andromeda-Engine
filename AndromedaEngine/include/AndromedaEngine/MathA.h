#pragma once

namespace AndromedaEngine
{
	class MathA
	{
	public:
		static const float PI;

	public:
		//Converts Degree angle into Radians
		static float Deg2Rad(float& angle);
		//Converts Radian angle into Degrees
		static float Rad2Deg(float& radians);
		//Clamps the given value between min and max values
		template<typename T>
		static T Clamp(T min, T value, T max);
		//Linearly interpolates From-To over time t
		static float Lerp(float start, float end, float t);
		//Returns absolute value of n ( -5 will become 5 )
		static float Abs(const float n);
	};
}
