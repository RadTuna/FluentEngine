#pragma once

// External Include
#include <cmath>

// Engine Include
#include "Core/Core.h"

constexpr float MATH_EPSILON = 1.e-4f;

class Math
{
public:

	static int32 Sign(int32 value);
	static float Signf(float value, float epsilon = MATH_EPSILON);

	template<typename T>
	static void Swap(T& a, T& b);
	
};

template <typename T>
void Math::Swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}
