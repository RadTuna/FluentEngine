
#include "Math/Vector4.h"
#include "Math/Matrix4x4.h"
#include "Math/Math.h"

namespace Fluent
{

	Vector4 Vector4::operator+(const Vector4& other) const
	{
		const f32 tempX = mX + other.mX;
		const f32 tempY = mY + other.mY;
		const f32 tempZ = mZ + other.mZ;

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
		const f32 tempX = mX - other.mX;
		const f32 tempY = mY - other.mY;
		const f32 tempZ = mZ - other.mZ;

		return Vector4(tempX, tempY, tempZ, 0.0f);
	}

	Vector4 Vector4::operator-=(const Vector4& other)
	{
		mX = mX - other.mX;
		mY = mY - other.mY;
		mZ = mZ - other.mZ;

		return Vector4(mX, mY, mZ, 0.0f);
	}

	Vector4 Vector4::operator*(f32 other) const
	{
		const f32 tempX = mX * other;
		const f32 tempY = mY * other;
		const f32 tempZ = mZ * other;

		return Vector4(tempX, tempY, tempZ, 0.0f);
	}

	Vector4 Vector4::operator*=(f32 other)
	{
		mX = mX * other;
		mY = mY * other;
		mZ = mZ * other;

		return Vector4(mX, mY, mZ, 0.0f);
	}

	Vector4 Vector4::operator*(const Matrix4x4& other) const
	{
		const f32 tempX = other.m11 * mX + other.m21 * mY + other.m31 * mZ + other.m41 * mW;
		const f32 tempY = other.m12 * mX + other.m22 * mY + other.m32 * mZ + other.m42 * mW;
		const f32 tempZ = other.m13 * mX + other.m23 * mY + other.m33 * mZ + other.m43 * mW;
		const f32 tempW = other.m14 * mX + other.m24 * mY + other.m34 * mZ + other.m44 * mW;

		return Vector4(tempX, tempY, tempZ, tempW);
	}

	Vector4 Vector4::operator*=(const Matrix4x4& other)
	{
		const f32 tempX = other.m11 * mX + other.m21 * mY + other.m31 * mZ + other.m41 * mW;
		const f32 tempY = other.m12 * mX + other.m22 * mY + other.m32 * mZ + other.m42 * mW;
		const f32 tempZ = other.m13 * mX + other.m23 * mY + other.m33 * mZ + other.m43 * mW;
		const f32 tempW = other.m14 * mX + other.m24 * mY + other.m34 * mZ + other.m44 * mW;

		mX = tempX;
		mY = tempY;
		mZ = tempZ;
		mW = tempW;

		return Vector4(tempX, tempY, tempZ, tempW);
	}

	f32 Vector4::operator*(const Vector4& other) const
	{
		return mX * other.mX + mY * other.mY + mZ * other.mZ;
	}

	Vector4 Vector4::operator^(const Vector4& other) const
	{
		const f32 tempX = mY * other.mZ - mZ * other.mY;
		const f32 tempY = mZ * other.mX - mX * other.mZ;
		const f32 tempZ = mX * other.mY - mY * other.mX;

		return Vector4(tempX, tempY, tempZ, 0.0f);
	}

	f32 Vector4::DotProduct(const Vector4& vectorA, const Vector4& vectorB)
	{
		return vectorA * vectorB;
	}

	Vector4 Vector4::CrossProduct(const Vector4& vectorA, const Vector4& vectorB)
	{
		return vectorA ^ vectorB;
	}

	f32 Vector4::Length() const
	{
		const f32 squareValue = mX * mX + mY * mY + mZ * mZ;
		return std::sqrtf(squareValue);
	}

	Vector4 Vector4::Normalize(const Vector4& other)
	{
		const f32 invVectorLength = 1.0f / other.Length();
		const f32 tempX = other.mX * invVectorLength;
		const f32 tempY = other.mY * invVectorLength;
		const f32 tempZ = other.mZ * invVectorLength;

		return Vector4(tempX, tempY, tempZ, 0.0f);
	}

	void Vector4::Normalize()
	{
		const f32 invVectorLength = 1.0f / Length();
		mX = mX * invVectorLength;
		mY = mY * invVectorLength;
		mZ = mZ * invVectorLength;
	}

}
