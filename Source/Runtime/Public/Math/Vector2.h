#pragma once

#pragma once


namespace Fluent
{

	class Vector2 final
	{
	public:

		float mX;
		float mY;

	public:

		explicit Vector2() = default;
		explicit constexpr Vector2(float x, float y) noexcept : mX(x), mY(y) {}

		~Vector2() = default;

		Vector2 operator+(const Vector2& other) const;
		Vector2 operator+=(const Vector2& other);

		Vector2 operator-(const Vector2& other) const;
		Vector2 operator-=(const Vector2& other);

		Vector2 operator*(float other) const;
		Vector2 operator*=(float other);

		float operator*(const Vector2& other) const;

		static float DotProduct(const Vector2& vectorA, const Vector2& vectorB);

		[[nodiscard]]
		float Length() const;

		static Vector2 Normalize(const Vector2& other);
		void Normalize();

	};

}
