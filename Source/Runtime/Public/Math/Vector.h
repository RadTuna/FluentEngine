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

	union alignas(16) FloatVector
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

		Vector SIMD_CALL operator=(const Vector& other) = delete;
		Vector SIMD_CALL operator=(Vector other);
		Vector SIMD_CALL operator=(__m128 other);

		Vector SIMD_CALL operator+(Vector other) const;
		Vector SIMD_CALL operator+=(Vector other);

		Vector SIMD_CALL operator-(Vector other) const;
		Vector SIMD_CALL operator-=(Vector other);

		Vector SIMD_CALL operator*(f32 other) const;
		Vector SIMD_CALL operator*=(f32 other);
		friend Vector SIMD_CALL operator*(f32 other, Vector thisVector);

		f32 SIMD_CALL operator*(Vector other) const;
		
		Vector SIMD_CALL operator*(Matrix other) const;
		Vector SIMD_CALL operator*=(Matrix other);

		Vector SIMD_CALL operator^(Vector other) const;

		static f32 SIMD_CALL DotProduct(Vector vectorA, Vector vectorB);

		static Vector SIMD_CALL CrossProduct(Vector vectorA, Vector vectorB);

		[[nodiscard]]
		f32 SIMD_CALL Length() const;

		static Vector SIMD_CALL Normalize(Vector other);
		void Normalize();

		static Vector SIMD_CALL LoadVector3(const class Vector3& inVector);
		static Vector SIMD_CALL LoadVector4(const class Vector4& inVector);

		static void SIMD_CALL StoreVector3(Vector inVector, class Vector3* outVector);
		static void SIMD_CALL StoreVector4(Vector inVector, class Vector4* outVector);

		static Vector SIMD_CALL SetVector3(f32 x, f32 y, f32 z);
		static Vector SIMD_CALL SetVector4(f32 x, f32 y, f32 z, f32 w);

	};

}
