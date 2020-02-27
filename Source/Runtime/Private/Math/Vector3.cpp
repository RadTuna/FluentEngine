
#include "Math/Vector3.h"
#include "Math/Matrix4x4.h"
#include "Math/Math.h"


using namespace Fluent;

Vector3 Vector3::operator+(const Vector3& other) const
{
	const float tempX = mX + other.mX;
	const float tempY = mY + other.mY;
	const float tempZ = mZ + other.mZ;

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
	const float tempX = mX - other.mX;
	const float tempY = mY - other.mY;
	const float tempZ = mZ - other.mZ;

	return Vector3(tempX, tempY, tempZ);
}

Vector3 Vector3::operator-=(const Vector3& other)
{
	mX = mX - other.mX;
	mY = mY - other.mY;
	mZ = mZ - other.mZ;

	return Vector3(mX, mY, mZ);
}

Vector3 Vector3::operator*(float other) const
{
	const float tempX = mX * other;
	const float tempY = mY * other;
	const float tempZ = mZ * other;

	return Vector3(tempX, tempY, tempZ);
}

Vector3 Vector3::operator*=(float other)
{
	mX = mX * other;
	mY = mY * other;
	mZ = mZ * other;

	return Vector3(mX, mY, mZ);
}

Vector3 Vector3::operator*(const Matrix4x4& other) const
{
	const float tempX = other.m11 * mX + other.m21 * mY + other.m31 * mZ;
	const float tempY = other.m12 * mX + other.m22 * mY + other.m32 * mZ;
	const float tempZ = other.m13 * mX + other.m23 * mY + other.m33 * mZ;

	return Vector3(tempX, tempY, tempZ);
}

Vector3 Vector3::operator*=(const Matrix4x4& other)
{
	const float tempX = other.m11 * mX + other.m21 * mY + other.m31 * mZ;
	const float tempY = other.m12 * mX + other.m22 * mY + other.m32 * mZ;
	const float tempZ = other.m13 * mX + other.m23 * mY + other.m33 * mZ;

	mX = tempX;
	mY = tempY;
	mZ = tempZ;
	
	return Vector3(tempX, tempY, tempZ);
}

float Vector3::operator*(const Vector3& other) const
{
	return mX * other.mX + mY * other.mY + mZ * other.mZ;
}

Vector3 Vector3::operator^(const Vector3& other) const
{
	const float tempX = mY * other.mZ - mZ * other.mY;
	const float tempY = mZ * other.mX - mX * other.mZ;
	const float tempZ = mX * other.mY - mY * other.mX;

	return Vector3(tempX, tempY, tempZ);
}

float Vector3::DotProduct(const Vector3& vectorA, const Vector3& vectorB)
{
	return vectorA * vectorB;
}

Vector3 Vector3::CrossProduct(const Vector3& vectorA, const Vector3& vectorB)
{
	return vectorA^ vectorB;
}

float Vector3::Length() const
{
	const float squareValue = mX * mX + mY * mY + mZ * mZ;
	return std::sqrtf(squareValue);
}

Vector3 Vector3::Normalize(const Vector3& other)
{
	const float invVectorLength = 1.0f / other.Length();
	const float tempX = other.mX * invVectorLength;
	const float tempY = other.mY * invVectorLength;
	const float tempZ = other.mZ * invVectorLength;

	return Vector3(tempX, tempY, tempZ);
}

void Vector3::Normalize()
{
	const float invVectorLength = 1.0f / Length();
	mX = mX * invVectorLength;
	mY = mY * invVectorLength;
	mZ = mZ * invVectorLength;
}
