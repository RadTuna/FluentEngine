#pragma once

// External Include
#include <cmath>

// Engine Include
#include "Core/Core.h"

constexpr float MATH_EPSILON = 1.e-4f;
constexpr float PI = 3.14159265358979323846264338327950288419716939937510f;
constexpr double D_PI = 3.14159265358979323846264338327950288419716939937510;

class Math
{
public:

	static int32 Sign(int32 value);
	static float Signf(float value, float epsilon = MATH_EPSILON);

	template<typename T>
	static void Swap(T& a, T& b);

	static constexpr float Rad2Deg(float radian);

	static constexpr float Deg2Rad(float degree);
	
};

constexpr float Math::Rad2Deg(float radian)
{
	return (radian / PI) * 180.0f;
}

constexpr float Math::Deg2Rad(float degree)
{
	return (degree / 180.0f) * PI;
}

template <typename T>
void Math::Swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}
