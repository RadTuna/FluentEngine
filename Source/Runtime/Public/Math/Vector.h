#pragma once

// External Include
#include <intrin.h> // common intrinsic
#include <xmmintrin.h> // SSE intrinsic
#include <emmintrin.h> // SSE2 intrinsic
#include <pmmintrin.h> // SSE3 intrinsic

// Engine Include
#include "Core/Core.h"


namespace Fluent
{

	union __declspec(align(16)) FloatVector
	{
		struct
		{
			f32 X;
			f32 Y;
			f32 Z;
			f32 W;
		};

		f32 Data[4];
	};

	class Matrix;
	
	class Vector final
	{
	public:

		__m128 mData;

	public:

		explicit Vector() noexcept;
		explicit constexpr Vector(const __m128& initData) noexcept : mData(initData) {}

		~Vector() = default;

		Vector __vectorcall operator=(const Vector& other) = delete;
		Vector __vectorcall operator=(Vector other);
		Vector __vectorcall operator=(__m128 other);

		Vector __vectorcall operator+(Vector other) const;
		Vector __vectorcall operator+=(Vector other);

		Vector __vectorcall operator-(Vector other) const;
		Vector __vectorcall operator-=(Vector other);

		Vector __vectorcall operator*(f32 other) const;
		Vector __vectorcall operator*=(f32 other);
		friend Vector __vectorcall operator*(f32 other, Vector thisVector);

		f32 __vectorcall operator*(Vector other) const;
		
		Vector __vectorcall operator*(Matrix other) const;
		Vector __vectorcall operator*=(Matrix other);

		Vector __vectorcall operator^(Vector other) const;

		static f32 __vectorcall DotProduct(Vector vectorA, Vector vectorB);

		static Vector __vectorcall CrossProduct(Vector vectorA, Vector vectorB);

		[[nodiscard]]
		f32 __vectorcall Length() const;

		static Vector __vectorcall Normalize(Vector other);
		void Normalize();

		static Vector __vectorcall LoadVector3(const class Vector3& inVector);
		static Vector __vectorcall LoadVector4(const class Vector4& inVector);

		static void __vectorcall StoreVector3(Vector inVector, class Vector3* outVector);
		static void __vectorcall StoreVector4(Vector inVector, class Vector4* outVector);

		static Vector __vectorcall SetVector3(f32 x, f32 y, f32 z);
		static Vector __vectorcall SetVector4(f32 x, f32 y, f32 z, f32 w);

	};

}
