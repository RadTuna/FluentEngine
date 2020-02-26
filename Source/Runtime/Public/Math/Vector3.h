#pragma once


namespace Fluent
{

	class Vector3
	{
	public:

		float mX;
		float mY;
		float mZ;

	public:

		explicit Vector3() = default;
		explicit constexpr Vector3(float x, float y, float z) noexcept : mX(x), mY(y), mZ(z) {}

		~Vector3() = default;

		explicit Vector3(const Vector3& other) = default;
		explicit Vector3(Vector3&& other) = default;

		Vector3& operator=(const Vector3& other) = default;
		Vector3& operator=(Vector3&& other) = default;

	};

}
