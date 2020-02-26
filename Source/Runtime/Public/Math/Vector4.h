#pragma once


namespace Fluent
{

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

		explicit Vector4(const Vector4& other) = default;
		explicit Vector4(Vector4&& other) = default;

		Vector4& operator=(const Vector4& other) = default;
		Vector4& operator=(Vector4&& other) = default;

	};

}