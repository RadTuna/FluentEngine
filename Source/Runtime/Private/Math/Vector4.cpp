
#include "Math/Vector4.h"
#include "Math/Matrix4x4.h"
#include "Math/Math.h"

namespace Fluent
{

	Vector4 Vector4::operator+(const Vector4& other) const
	{
		const float tempX = mX + other.mX;
		const float tempY = mY + other.mY;
		const float tempZ = mZ + other.mZ;

		return Vector4(tempX, tempY, tempZ, 0.0f);
	}

	Vector4 Vector4::operator+=(const Vector4& other)
	{
		mX = mX + other.mX;
		mY = mY + other.mY;
		mZ = mZ + other.mZ;

		return Vector4(mX, mY, mZ, 0.0f);
	}

	Vector4 Vector4::operator-(const Vector4& other) const
	{
		const float tempX = mX - other.mX;
		const float tempY = mY - other.mY;
		const float tempZ = mZ - other.mZ;

		return Vector4(tempX, tempY, tempZ, 0.0f);
	}

	Vector4 Vector4::operator-=(const Vector4& other)
	{
		mX = mX - other.mX;
		mY = mY - other.mY;
		mZ = mZ - other.mZ;

		return Vector4(mX, mY, mZ, 0.0f);
	}

	Vector4 Vector4::operator*(float other) const
	{
		const float tempX = mX * other;
		const float tempY = mY * other;
		const float tempZ = mZ * other;

		return Vector4(tempX, tempY, tempZ, 0.0f);
	}

	Vector4 Vector4::operator*=(float other)
	{
		mX = mX * other;
		mY = mY * other;
		mZ = mZ * other;

		return Vector4(mX, mY, mZ, 0.0f);
	}

	Vector4 Vector4::operator*(const Matrix4x4& other) const
	{
		const float tempX = other.m11 * mX + other.m21 * mY + other.m31 * mZ + other.m41 * mW;
		const float tempY = other.m12 * mX + other.m22 * mY + other.m32 * mZ + other.m42 * mW;
		const float tempZ = other.m13 * mX + other.m23 * mY + other.m33 * mZ + other.m43 * mW;
		const float tempW = other.m14 * mX + other.m24 * mY + other.m34 * mZ + other.m44 * mW;

		return Vector4(tempX, tempY, tempZ, tempW);
	}

	Vector4 Vector4::operator*=(const Matrix4x4& other)
	{
		const float tempX = other.m11 * mX + other.m21 * mY + other.m31 * mZ + other.m41 * mW;
		const float tempY = other.m12 * mX + other.m22 * mY + other.m32 * mZ + other.m42 * mW;
		const float tempZ = other.m13 * mX + other.m23 * mY + other.m33 * mZ + other.m43 * mW;
		const float tempW = other.m14 * mX + other.m24 * mY + other.m34 * mZ + other.m44 * mW;

		mX = tempX;
		mY = tempY;
		mZ = tempZ;
		mW = tempW;

		return Vector4(tempX, tempY, tempZ, tempW);
	}

	float Vector4::operator*(const Vector4& other) const
	{
		return mX * other.mX + mY * other.mY + mZ * other.mZ;
	}

	Vector4 Vector4::operator^(const Vector4& other) const
	{
		const float tempX = mY * other.mZ - mZ * other.mY;
		const float tempY = mZ * other.mX - mX * other.mZ;
		const float tempZ = mX * other.mY - mY * other.mX;

		return Vector4(tempX, tempY, tempZ, 0.0f);
	}

	float Vector4::DotProduct(const Vector4& vectorA, const Vector4& vectorB)
	{
		return vectorA * vectorB;
	}

	Vector4 Vector4::CrossProduct(const Vector4& vectorA, const Vector4& vectorB)
	{
		return vectorA ^ vectorB;
	}

	float Vector4::Length() const
	{
		const float squareValue = mX * mX + mY * mY + mZ * mZ;
		return std::sqrtf(squareValue);
	}

	Vector4 Vector4::Normalize(const Vector4& other)
	{
		const float invVectorLength = 1.0f / other.Length();
		const float tempX = other.mX * invVectorLength;
		const float tempY = other.mY * invVectorLength;
		const float tempZ = other.mZ * invVectorLength;

		return Vector4(tempX, tempY, tempZ, 0.0f);
	}

	void Vector4::Normalize()
	{
		const float invVectorLength = 1.0f / Length();
		mX = mX * invVectorLength;
		mY = mY * invVectorLength;
		mZ = mZ * invVectorLength;
	}

}
