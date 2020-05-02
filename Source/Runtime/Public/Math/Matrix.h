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
	class Vector;
	
	class Matrix final
	{
	public:

		__m128 mRow1;
		__m128 mRow2;
		__m128 mRow3;
		__m128 mRow4;

	public:

		explicit Matrix() noexcept;
		explicit Matrix(const __m128& inRow1, const __m128& inRow2, const __m128& inRow3, const __m128& inRow4) noexcept;
		explicit Matrix(Vector inRow1, Vector inRow2, Vector inRow3, Vector inRow4) noexcept;

		~Matrix() = default;
		 
		Matrix SIMD_CALL operator=(const Matrix & other) = delete;
		Matrix SIMD_CALL operator=(Matrix other);

		Vector SIMD_CALL operator*(Vector other) const;

		Matrix SIMD_CALL operator*(Matrix other) const;
		Matrix SIMD_CALL operator*=(Matrix other);

		static Matrix SIMD_CALL Transpose(Matrix other);
		void Transpose();

		static Matrix SIMD_CALL CreateLookAtLH(Vector cameraPosition, Vector targetPosition, Vector upVector);
		static Matrix SIMD_CALL CreateOrthographicLH(f32 width, f32 height, f32 near, f32 far);
		static Matrix SIMD_CALL CreatePerspectiveLH(f32 width, f32 height, f32 near, f32 far);
		static Matrix SIMD_CALL CreatePerspectiveFovLH(f32 fov, f32 aspectRatio, f32 near, f32 far);

		static Matrix SIMD_CALL LoadMatrix4X4(const class Matrix4x4& inMatrix);

		static void SIMD_CALL StoreMatrix4X4(Matrix inMatrix, class Matrix4x4* outMatrix);

		static float SIMD_CALL DotSIMD(__m128 vector1, __m128 vector2);

		static const Matrix Identity;
		
	};
}
