
#include "Math/Vector2.h"
#include "Math/Math.h"


namespace Fluent
{

	const Vector2 Vector2::Zero = Vector2(0.0f, 0.0f);
	const Vector2 Vector2::OneX = Vector2(1.0f, 0.0f);
	const Vector2 Vector2::OneY = Vector2(0.0f, 1.0f);
	
	Vector2 Vector2::operator+(const Vector2& other) const
	{
		const f32 tempX = mX + other.mX;
		const f32 tempY = mY + other.mY;

		return Vector2(tempX, tempY);
	}

	Vector2 Vector2::operator+=(const Vector2& other)
	{
		mX = mX + other.mX;
		mY = mY + other.mY;

		return Vector2(mX, mY);
	}

	Vector2 Vector2::operator-(const Vector2& other) const
	{
		const f32 tempX = mX - other.mX;
		const f32 tempY = mY - other.mY;

		return Vector2(tempX, tempY);
	}

	Vector2 Vector2::operator-=(const Vector2& other)
	{
		mX = mX - other.mX;
		mY = mY - other.mY;

		return Vector2(mX, mY);
	}

	Vector2 Vector2::operator*(f32 other) const
	{
		const f32 tempX = mX * other;
		const f32 tempY = mY * other;

		return Vector2(tempX, tempY);
	}

	Vector2 Vector2::operator*=(f32 other)
	{
		mX = mX * other;
		mY = mY * other;

		return Vector2(mX, mY);
	}

	f32 Vector2::operator*(const Vector2& other) const
	{
		return mX * other.mX + mY * other.mY;
	}

	float Vector2::DotProduct(const Vector2& vectorA, const Vector2& vectorB)
	{
		return vectorA * vectorB;
	}

	float Vector2::Length() const
	{
		const f32 squareValue = mX * mX + mY * mY;
		return std::sqrtf(squareValue);
	}

	Vector2 Vector2::Normalize(const Vector2& other)
	{
		const f32 invVectorLength = 1.0f / other.Length();
		const f32 tempX = other.mX * invVectorLength;
		const f32 tempY = other.mY * invVectorLength;

		return Vector2(tempX, tempY);
	}

	void Vector2::Normalize()
	{
		const f32 invVectorLength = 1.0f / Length();
		mX = mX * invVectorLength;
		mY = mY * invVectorLength;
	}

}
