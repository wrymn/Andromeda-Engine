#pragma once
#include "Vector.h"

namespace AndromedaEngine
{
	struct Matrix2
	{
		float r0c0;
		float r0c1;
		float r1c0;
		float r1c1;

		inline Matrix2(float r0c0, float r0c1, float r1c0, float r1c1) : r0c0(r1c0), r0c1(r0c1), r1c0(r1c0), r1c1(r1c1){};
		inline Matrix2() : r0c0(1), r0c1(0), r1c0(0), r1c1(1){};
	};
}