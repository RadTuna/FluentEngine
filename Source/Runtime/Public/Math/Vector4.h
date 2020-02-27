#pragma once


namespace Fluent
{
	class Matrix4x4;
	
	class Vector4
	{
	public:

		float mX;
		float mY;
		float mZ;
		float mW;

	public:

		explicit Vector4() = default;
		explicit constexpr Vector4(float x, float y, float z, float w) noexcept : mX(x), mY(y), mZ(z), mW(w) {}

		~Vector4() = default;

		Vector4 operator+(const Vector4& other) const;
		Vector4 operator+=(const Vector4& other);

		Vector4 operator-(const Vector4& other) const;
		Vector4 operator-=(const Vector4& other);

		Vector4 operator*(float other) const;
		Vector4 operator*=(float other);

		Vector4 operator*(const Matrix4x4& other) const;
		Vector4 operator*=(const Matrix4x4& other);
		
		float operator*(const Vector4& other) const;

		Vector4 operator^(const Vector4& other) const;

		static float DotProduct(const Vector4& vectorA, const Vector4& vectorB);

		static Vector4 CrossProduct(const Vector4& vectorA, const Vector4& vectorB);

		[[nodiscard]]
		float Length() const;

		static Vector4 Normalize(const Vector4 & other);
		void Normalize();

	};

}