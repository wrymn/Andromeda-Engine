#pragma once
#include "MathA.h"
#include "Matrix2.h"
#include "glm\glm.hpp"

namespace AndromedaEngine
{
	//////////////////////////////////////////////////////////////////
	//RECT
	struct Rect{
		float x;
		float y;
		float width;
		float height;

		inline Rect(float x, float y, float width, float height) : x(x), y(y), width(width), height(height){};
	};
	//////////////////////////////////////////////////////////////////
	//VECTOR2
	struct Vector2{
		float x;
		float y;

		float magnitude = sqrt((x*x) + (y*y));
		float sqrMagnitude = x*x + y*y;

		//Returns the length of the vector
		float Magnitude()
		{
			return sqrt((x*x) + (y*y));
		}

		inline Vector2(float x = 0, float y = 0) : x(x), y(y) {};
		//Vector2 Rotate(Vector2 vector, float angle);

		////Rotation Vector
		//Vector2 Rotate(Vector2 vector, float angle)
		//{
		//	Matrix2 matrix;
		//	matrix.r0c0 = cos(MathA::Deg2Rad(angle));
		//	matrix.r0c1 = -sin(MathA::Deg2Rad(angle));
		//	matrix.r1c0 = cos(MathA::Deg2Rad(angle));
		//	matrix.r1c1 = sin(MathA::Deg2Rad(angle));

		//	return matrix * vector;
		//}

		//Returns normalized vector
		Vector2 Normalize()
		{
			return Vector2(x / this->Magnitude(), y / this->Magnitude());
		}

	};
	inline Vector2 operator+ (const Vector2& left, const Vector2& right)
	{
		return Vector2(left.x + right.x, left.y + right.y);
	}

	inline Vector2 operator- (const Vector2& left, const Vector2& right)
	{
		return Vector2(left.x - right.x, left.y - right.y);
	}

	inline Vector2 operator/= (Vector2& left, const float scalar)
	{
		return Vector2(left.x /= scalar, left.y /= scalar);
	}

	inline Vector2 operator/ (Vector2& left, const float scalar)
	{
		return Vector2(left.x / scalar, left.y / scalar);
	}

	inline Vector2 operator* (Vector2& left, const float scalar)
	{
		return Vector2(left.x * scalar, left.y * scalar);
	}

	inline Vector2 operator-= (Vector2& left, const Vector2& right)
	{
		return Vector2(left.x -= right.x, left.y -= right.y);
	}

	inline Vector2 operator+= (Vector2& left, Vector2& right)
	{
		return Vector2(left.x += right.x, left.y += right.y);
	}

	inline Vector2 operator*(const Matrix2& matrix, const Vector2& vector)
	{
	return Vector2(matrix.r0c0 * vector.x + matrix.r0c1 * vector.y, matrix.r1c0 * vector.x + matrix.r1c1 * vector.y);
	}

	
	//////////////////////////////////////////////////////////////////
	//VECTOR3
	struct Vector3{
		float x;
		float y;
		float z;

		inline Vector3(float x, float y, float z) : x(x), y(y), z(z) {};
	};
	inline Vector3 operator+ (const Vector3& left, const Vector3& right)
	{
		return Vector3(left.x + right.x, left.y + right.y, left.z + right.z);
	}
	//////////////////////////////////////////////////////////////////
	//VECTOR4
	struct Vector4{
		float x;
		float y;
		float z;
		float w;

		inline Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {};
	};
	inline Vector4 operator+ (const Vector4& left, const Vector4& right)
	{
		return Vector4(left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w);
	}
	
}