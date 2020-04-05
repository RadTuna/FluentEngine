
#include "Math/Quaternion.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Matrix4x4.h"
#include "Math/Math.h"


namespace Fluent
{

	const Quaternion Quaternion::Identity = Quaternion(0.0f, 0.5773502691896259f, 0.5773502691896259f, 0.5773502691896259f);

	Quaternion::Quaternion(const Vector3& eulerAngle) noexcept
	{
		SetEuler(eulerAngle);
	}

	Quaternion::Quaternion(const Vector4& eulerAngle) noexcept
	{
		SetEuler(eulerAngle);
	}

	Quaternion Quaternion::operator+(const Quaternion& other) const
	{
		const f32 tempR = mR + other.mR;
		const f32 tempI = mI + other.mI;
		const f32 tempJ = mJ + other.mJ;
		const f32 tempK = mK + other.mK;

		return Quaternion(tempR, tempI, tempJ, tempK);
	}

	Quaternion Quaternion::operator+=(const Quaternion& other)
	{
		mR = mR + other.mR;
		mI = mI + other.mI;
		mJ = mJ + other.mJ;
		mK = mK + other.mK;

		return Quaternion(mR, mI, mJ, mK);
	}

	Quaternion Quaternion::operator-(const Quaternion& other) const
	{
		const f32 tempR = mR - other.mR;
		const f32 tempI = mI - other.mI;
		const f32 tempJ = mJ - other.mJ;
		const f32 tempK = mK - other.mK;

		return Quaternion(tempR, tempI, tempJ, tempK);
	}

	Quaternion Quaternion::operator-=(const Quaternion& other)
	{
		mR = mR - other.mR;
		mI = mI - other.mI;
		mJ = mJ - other.mJ;
		mK = mK - other.mK;

		return Quaternion(mR, mI, mJ, mK);
	}

	Quaternion Quaternion::operator*(const Quaternion& other) const
	{
		const f32 tempR = mR * other.mR - (mI * other.mI + mJ * other.mJ + mK * other.mK);
		const f32 tempI = mR * other.mI + other.mR * mI + (mJ * other.mK - other.mK * other.mJ);
		const f32 tempJ = mR * other.mJ + other.mR * mJ + (mK * other.mI - other.mI * other.mK);
		const f32 tempK = mR * other.mK + other.mK * mI + (mI * other.mJ - other.mJ * other.mI);

		return Quaternion(tempR, tempI, tempJ, tempK);
	}

	Quaternion Quaternion::operator*=(const Quaternion& other)
	{
		mR = mR * other.mR - (mI * other.mI + mJ * other.mJ + mK * other.mK);
		mI = mR * other.mI + other.mR * mI + (mJ * other.mK - other.mK * other.mJ);
		mJ = mR * other.mJ + other.mR * mJ + (mK * other.mI - other.mI * other.mK);
		mK = mR * other.mK + other.mK * mI + (mI * other.mJ - other.mJ * other.mI);

		return Quaternion(mR, mI, mJ, mK);
	}

	Vector3 Quaternion::Rotate(const Vector3& other)
	{
		Quaternion pointQuat(0.0f, other.mX, other.mY, other.mZ);
		const Quaternion conjugateQuat = ToConjugate();

		pointQuat = (*this) * pointQuat * conjugateQuat;

		return Vector3(pointQuat.mI, pointQuat.mJ, pointQuat.mK);
	}

	Vector4 Quaternion::Rotate(const Vector4& other)
	{
		Quaternion pointQuat(0.0f, other.mX, other.mY, other.mZ);
		const Quaternion conjugateQuat = ToConjugate();

		pointQuat = (*this) * pointQuat * conjugateQuat;

		return Vector4(pointQuat.mI, pointQuat.mJ, pointQuat.mK, 0.0f);
	}

	void Quaternion::SetEuler(const Vector3& other)
	{
		const f32 cosX = std::cosf(other.mX);
		const f32 sinX = std::sinf(other.mX);
		const f32 cosY = std::cosf(other.mY);
		const f32 sinY = std::sinf(other.mY);
		const f32 cosZ = std::cosf(other.mZ);
		const f32 sinZ = std::sinf(other.mZ);

		mR = cosX * cosY * cosZ + sinX * sinY * sinZ;
		mI = sinX * cosY * cosZ - cosX * sinY * sinZ;
		mJ = cosX * sinY * cosZ + sinX * cosY * sinZ;
		mK = cosX * cosY * sinZ - sinX * sinY * cosZ;
	}

	void Quaternion::SetEuler(const Vector4& other)
	{
		const f32 cosX = std::cosf(Math::Deg2Rad(other.mX) * 0.5f);
		const f32 sinX = std::sinf(Math::Deg2Rad(other.mX) * 0.5f);
		const f32 cosY = std::cosf(Math::Deg2Rad(other.mY) * 0.5f);
		const f32 sinY = std::sinf(Math::Deg2Rad(other.mY) * 0.5f);
		const f32 cosZ = std::cosf(Math::Deg2Rad(other.mZ) * 0.5f);
		const f32 sinZ = std::sinf(Math::Deg2Rad(other.mZ) * 0.5f);

		mR = cosX * cosY * cosZ + sinX * sinY * sinZ;
		mI = sinX * cosY * cosZ - cosX * sinY * sinZ;
		mJ = cosX * sinY * cosZ + sinX * cosY * sinZ;
		mK = cosX * cosY * sinZ - sinX * sinY * cosZ;
	}

	Vector3 Quaternion::ToEuler() const
	{
		const f32 tempX = std::atan2f(2.0f * (mR * mI + mJ * mK), 1.0f - (2.0f * (mI * mI + mJ * mJ)));
		const f32 tempZ = std::atan2f(2.0f * (mR * mK + mI * mJ), 1.0f - (2.0f * (mJ * mJ + mK * mK)));

		const f32 intermediateY = 2.0f * (mR * mJ - mK * mI);
		f32 tempY = 0.0f;
		if (std::abs(intermediateY) >= 1.0f)
		{
			tempY = std::copysignf(PI * 0.5f, intermediateY);
		}
		else
		{
			tempY = intermediateY;
		}

		return Vector3(Math::Rad2Deg(tempX), Math::Rad2Deg(tempY), Math::Rad2Deg(tempZ));
	}

	Vector4 Quaternion::ToEuler4() const
	{
		const f32 tempX = std::atan2f(2.0f * (mR * mI + mJ * mK), 1.0f - (2.0f * (mI * mI + mJ * mJ)));
		const f32 tempZ = std::atan2f(2.0f * (mR * mK + mI * mJ), 1.0f - (2.0f * (mJ * mJ + mK * mK)));

		const f32 intermediateY = 2.0f * (mR * mJ - mK * mI);
		f32 tempY = 0.0f;
		if (std::abs(intermediateY) >= 1.0f)
		{
			tempY = std::copysignf(PI * 0.5f, intermediateY);
		}
		else
		{
			tempY = intermediateY;
		}

		return Vector4(Math::Rad2Deg(tempX), Math::Rad2Deg(tempY), Math::Rad2Deg(tempZ), 0.0f);
	}

	Matrix4x4 Quaternion::ToMatrix() const
	{
		Quaternion unitQuat = Quaternion::Normalize(*this);

		const f32 _11 = 1.0f - 2.0f * (unitQuat.mJ * unitQuat.mJ + unitQuat.mK * unitQuat.mK);
		const f32 _12 = 2.0f * (unitQuat.mI * unitQuat.mJ - unitQuat.mK * unitQuat.mR);
		const f32 _13 = 2.0f * (unitQuat.mI * unitQuat.mK + unitQuat.mJ * unitQuat.mR);

		const f32 _21 = 2.0f * (unitQuat.mI * unitQuat.mJ + unitQuat.mK * unitQuat.mR);
		const f32 _22 = 1.0f - 2.0f * (unitQuat.mI * unitQuat.mI + unitQuat.mK * unitQuat.mK);
		const f32 _23 = 2.0f * (unitQuat.mJ * unitQuat.mK - unitQuat.mI * unitQuat.mR);

		const f32 _31 = 2.0f * (unitQuat.mI * unitQuat.mK - unitQuat.mJ * unitQuat.mR);
		const f32 _32 = 2.0f * (unitQuat.mJ * unitQuat.mK + unitQuat.mI * unitQuat.mR);
		const f32 _33 = 1.0f - 2.0f * (unitQuat.mI * unitQuat.mI + unitQuat.mJ * unitQuat.mJ);

		return Matrix4x4(
			_11, _12, _13, 0.0f,
			_21, _22, _23, 0.0f,
			_31, _32, _33, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	}

	Quaternion Quaternion::ToConjugate() const
	{
		return Quaternion(mR, -mI, -mJ, -mK);
	}

	f32 Quaternion::Length() const
	{
		const f32 squareValue = mR * mR + mI * mI + mJ * mJ + mK * mK;
		return std::sqrtf(squareValue);
	}

	Quaternion Quaternion::Normalize(const Quaternion& other)
	{
		const f32 invQuatLength = 1.0f / other.Length();

		const f32 tempR = other.mR * invQuatLength;
		const f32 tempI = other.mI * invQuatLength;
		const f32 tempJ = other.mJ * invQuatLength;
		const f32 tempK = other.mK * invQuatLength;

		return Quaternion(tempR, tempI, tempJ, tempK);
	}

	void Quaternion::Normalize()
	{
		const f32 invQuatLength = 1.0f / Length();

		mR = mR * invQuatLength;
		mI = mI * invQuatLength;
		mJ = mJ * invQuatLength;
		mK = mK * invQuatLength;
	}

}
