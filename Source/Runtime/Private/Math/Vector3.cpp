
#include "Math/Vector3.h"
#include "Math/Matrix4x4.h"
#include "Math/Math.h"


namespace Fluent
{

	Vector3 Vector3::operator+(const Vector3& other) const
	{
		const f32 tempX = mX + other.mX;
		const f32 tempY = mY + other.mY;
		const f32 tempZ = mZ + other.mZ;

		return Vector3(tempX, tempY, tempZ);
	}

	Vector3 Vector3::operator+=(const Vector3& other)
	{
		mX = mX + other.mX;
		mY = mY + other.mY;
		mZ = mZ + other.mZ;

		return Vector3(mX, mY, mZ);
	}

	Vector3 Vector3::operator-(const Vector3& other) const
	{
		const f32 tempX = mX - other.mX;
		const f32 tempY = mY - other.mY;
		const f32 tempZ = mZ - other.mZ;

		return Vector3(tempX, tempY, tempZ);
	}

	Vector3 Vector3::operator-=(const Vector3& other)
	{
		mX = mX - other.mX;
		mY = mY - other.mY;
		mZ = mZ - other.mZ;

		return Vector3(mX, mY, mZ);
	}

	Vector3 Vector3::operator*(f32 other) const
	{
		const f32 tempX = mX * other;
		const f32 tempY = mY * other;
		const f32 tempZ = mZ * other;

		return Vector3(tempX, tempY, tempZ);
	}

	Vector3 Vector3::operator*=(f32 other)
	{
		mX = mX * other;
		mY = mY * other;
		mZ = mZ * other;

		return Vector3(mX, mY, mZ);
	}

	Vector3 Vector3::operator*(const Matrix4x4& other) const
	{
		const f32 tempX = other.m11 * mX + other.m21 * mY + other.m31 * mZ;
		const f32 tempY = other.m12 * mX + other.m22 * mY + other.m32 * mZ;
		const f32 tempZ = other.m13 * mX + other.m23 * mY + other.m33 * mZ;

		return Vector3(tempX, tempY, tempZ);
	}

	Vector3 Vector3::operator*=(const Matrix4x4& other)
	{
		const f32 tempX = other.m11 * mX + other.m21 * mY + other.m31 * mZ;
		const f32 tempY = other.m12 * mX + other.m22 * mY + other.m32 * mZ;
		const f32 tempZ = other.m13 * mX + other.m23 * mY + other.m33 * mZ;

		mX = tempX;
		mY = tempY;
		mZ = tempZ;

		return Vector3(tempX, tempY, tempZ);
	}

	f32 Vector3::operator*(const Vector3& other) const
	{
		return mX * other.mX + mY * other.mY + mZ * other.mZ;
	}

	Vector3 Vector3::operator^(const Vector3& other) const
	{
		const f32 tempX = mY * other.mZ - mZ * other.mY;
		const f32 tempY = mZ * other.mX - mX * other.mZ;
		const f32 tempZ = mX * other.mY - mY * other.mX;

		return Vector3(tempX, tempY, tempZ);
	}

	f32 Vector3::DotProduct(const Vector3& vectorA, const Vector3& vectorB)
	{
		return vectorA * vectorB;
	}

	Vector3 Vector3::CrossProduct(const Vector3& vectorA, const Vector3& vectorB)
	{
		return vectorA ^ vectorB;
	}

	f32 Vector3::Length() const
	{
		const f32 squareValue = mX * mX + mY * mY + mZ * mZ;
		return std::sqrtf(squareValue);
	}

	Vector3 Vector3::Normalize(const Vector3& other)
	{
		const f32 invVectorLength = 1.0f / other.Length();
		const f32 tempX = other.mX * invVectorLength;
		const f32 tempY = other.mY * invVectorLength;
		const f32 tempZ = other.mZ * invVectorLength;

		return Vector3(tempX, tempY, tempZ);
	}

	void Vector3::Normalize()
	{
		const f32 invVectorLength = 1.0f / Length();
		mX = mX * invVectorLength;
		mY = mY * invVectorLength;
		mZ = mZ * invVectorLength;
	}

}
