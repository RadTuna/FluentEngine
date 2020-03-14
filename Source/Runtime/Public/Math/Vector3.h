#pragma once


namespace Fluent
{
	class Matrix4x4;
	
	class Vector3 final
	{
	public:

		float mX;
		float mY;
		float mZ;

	public:

		explicit Vector3() = default;
		explicit constexpr Vector3(float x, float y, float z) noexcept : mX(x), mY(y), mZ(z) {}

		~Vector3() = default;

		Vector3 operator+(const Vector3& other) const;
		Vector3 operator+=(const Vector3& other);

		Vector3 operator-(const Vector3& other) const;
		Vector3 operator-=(const Vector3& other);

		Vector3 operator*(float other) const;
		Vector3 operator*=(float other);

		Vector3 operator*(const Matrix4x4& other) const;
		Vector3 operator*=(const Matrix4x4& other);

		float operator*(const Vector3& other) const;

		Vector3 operator^(const Vector3& other) const;

		static float DotProduct(const Vector3& vectorA, const Vector3& vectorB);

		static Vector3 CrossProduct(const Vector3& vectorA, const Vector3& vectorB);

		[[nodiscard]]
		float Length() const;

		static Vector3 Normalize(const Vector3& other);
		void Normalize();

	};

}
