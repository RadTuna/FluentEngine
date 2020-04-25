#pragma once

// Engine Include
#include "Core/TypeDefinition.h"


namespace Fluent
{
	class Matrix4x4;
	
	class Vector3 final
	{
	public:

		f32 mX;
		f32 mY;
		f32 mZ;

	public:

		explicit Vector3() = default;
		explicit constexpr Vector3(f32 x, f32 y, f32 z) noexcept : mX(x), mY(y), mZ(z) {}

		~Vector3() = default;

		Vector3 operator+(const Vector3& other) const;
		Vector3 operator+=(const Vector3& other);

		Vector3 operator-(const Vector3& other) const;
		Vector3 operator-=(const Vector3& other);

		Vector3 operator*(f32 other) const;
		Vector3 operator*=(f32 other);

		Vector3 operator*(const Matrix4x4& other) const;
		Vector3 operator*=(const Matrix4x4& other);

		f32 operator*(const Vector3& other) const;

		Vector3 operator^(const Vector3& other) const;

		static f32 DotProduct(const Vector3& vectorA, const Vector3& vectorB);

		static Vector3 CrossProduct(const Vector3& vectorA, const Vector3& vectorB);

		[[nodiscard]]
		f32 Length() const;

		static Vector3 Normalize(const Vector3& other);
		void Normalize();

	};

}
