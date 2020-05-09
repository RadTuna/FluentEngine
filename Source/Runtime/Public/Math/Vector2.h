#pragma once

// Engine Include
#include "Core/TypeDefinition.h"


namespace Fluent
{

	class Vector2 final
	{
	public:

		f32 mX;
		f32 mY;

	public:

		explicit Vector2() = default;
		explicit constexpr Vector2(f32 x, f32 y) noexcept : mX(x), mY(y) {}

		~Vector2() = default;

		Vector2 operator+(const Vector2& other) const;
		Vector2 operator+=(const Vector2& other);

		Vector2 operator-(const Vector2& other) const;
		Vector2 operator-=(const Vector2& other);

		Vector2 operator*(f32 other) const;
		Vector2 operator*=(f32 other);

		f32 operator*(const Vector2& other) const;

		static f32 DotProduct(const Vector2& vectorA, const Vector2& vectorB);

		[[nodiscard]]
		f32 Length() const;

		static Vector2 Normalize(const Vector2& other);
		void Normalize();

		static const Vector2 Zero;
		static const Vector2 OneX;
		static const Vector2 OneY;
		
	};

}
