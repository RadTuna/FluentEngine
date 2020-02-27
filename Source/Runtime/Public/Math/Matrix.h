#pragma once

// External Include
#include <intrin.h> // common intrinsic
#include <xmmintrin.h> // SSE intrinsic
#include <emmintrin.h> // SSE2 intrinsic
#include <pmmintrin.h> // SSE3 intrinsic


namespace Fluent
{
	class Vector;
	
	class Matrix
	{
	public:

		__m128 mRow1;
		__m128 mRow2;
		__m128 mRow3;
		__m128 mRow4;

	public:

		explicit Matrix() noexcept;
		explicit Matrix(const __m128& inRow1, const __m128& inRow2, const __m128& inRow3, const __m128& inRow4) noexcept;

		~Matrix() = default;
		 
		Matrix __vectorcall operator=(const Matrix & other) = delete;
		Matrix __vectorcall operator=(Matrix other);

		Vector __vectorcall operator*(Vector other) const;

		Matrix __vectorcall operator*(Matrix other) const;
		Matrix __vectorcall operator*=(Matrix other);

		static Matrix __vectorcall Transpose(Matrix other);
		void Transpose();

		static Matrix __vectorcall LoadMatrix4X4(const class Matrix4x4& inMatrix);

		static void __vectorcall StoreMatrix4X4(Matrix inMatrix, class Matrix4x4* outMatrix);

		static float __vectorcall DotSIMD(__m128 vector1, __m128 vector2);
		
	};
}
