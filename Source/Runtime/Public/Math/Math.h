#pragma once

// External Include
#include <cmath>

// Engine Include
#include "Core/Core.h"

namespace Fluent
{

	constexpr f32 MATH_EPSILON = 1.e-4f;
	constexpr f32 PI = 3.14159265358979323846264338327950288419716939937510f;
	constexpr double D_PI = 3.14159265358979323846264338327950288419716939937510;

	class Math final
	{
	public:

		static i32 Sign(i32 value);
		static f32 Signf(f32 value, f32 epsilon = MATH_EPSILON);

		template<typename T>
		static void Swap(T& a, T& b);

		static constexpr f32 Rad2Deg(f32 radian);

		static constexpr f32 Deg2Rad(f32 degree);

	};

	constexpr f32 Math::Rad2Deg(f32 radian)
	{
		return (radian / PI) * 180.0f;
	}

	constexpr f32 Math::Deg2Rad(f32 degree)
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

}
