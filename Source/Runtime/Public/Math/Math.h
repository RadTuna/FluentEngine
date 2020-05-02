#pragma once

// External Include
#include <cmath>

// Engine Include
#include "Core/TypeDefinition.h"

namespace Fluent
{
	namespace Math
	{
		constexpr f32 MATH_EPSILON = 1.e-4f;
		constexpr f32 PI = 3.14159265358979323846264338327950288419716939937510f;
		constexpr double D_PI = 3.14159265358979323846264338327950288419716939937510;

		static i32 Sign(i32 value);
		static f32 Signf(f32 value, f32 epsilon = MATH_EPSILON);

		constexpr f32 Rad2Deg(f32 radian)
		{
			return (radian / PI) * 180.0f;
		}

		constexpr f32 Deg2Rad(f32 degree)
		{
			return (degree / 180.0f) * PI;
		}

		template <typename T>
		void Swap(T& a, T& b)
		{
			T temp = a;
			a = b;
			b = temp;
		}

	}

}
