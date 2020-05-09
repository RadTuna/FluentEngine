#pragma once

// Engine Include
#include "Core/TypeDefinition.h"

namespace Fluent
{
	class Matrix4x4;
	
	class Vector4 final
	{
	public:

		f32 mX;
		f32 mY;
		f32 mZ;
		f32 mW;

	public:

		explicit Vector4() = default;
		explicit constexpr Vector4(f32 x, f32 y, f32 z, f32 w) noexcept : mX(x), mY(y), mZ(z), mW(w) {}

		~Vector4() = default;

		Vector4 operator+(const Vector4& other) const;
		Vector4 operator+=(const Vector4& other);

		Vector4 operator-(const Vector4& other) const;
		Vector4 operator-=(const Vector4& other);

		Vector4 operator*(f32 other) const;
		Vector4 operator*=(f32 other);

		Vector4 operator*(const Matrix4x4& other) const;
		Vector4 operator*=(const Matrix4x4& other);
		
		f32 operator*(const Vector4& other) const;

		Vector4 operator^(const Vector4& other) const;

		static f32 DotProduct(const Vector4& vectorA, const Vector4& vectorB);

		static Vector4 CrossProduct(const Vector4& vectorA, const Vector4& vectorB);
		
		[[nodiscard]]
		f32 Length() const;

		static Vector4 Normalize(const Vector4 & other);
		void Normalize();

		static const Vector4 Zero;
		static const Vector4 OneX;
		static const Vector4 OneY;
		static const Vector4 OneZ;

	};

}