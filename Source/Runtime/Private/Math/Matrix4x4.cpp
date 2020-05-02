
#include "Math/Matrix4x4.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Math.h"


namespace Fluent
{

	const Matrix4x4 Matrix4x4::Identity = Matrix4x4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
	
	Matrix4x4::Matrix4x4(const Vector4& row1, const Vector4& row2, const Vector4& row3, const Vector4& row4) noexcept
	{
		m11 = row1.mX; m12 = row1.mY; m13 = row1.mZ; m14 = row1.mW;
		m21 = row2.mX; m22 = row2.mY; m23 = row2.mZ; m24 = row2.mW;
		m31 = row3.mX; m32 = row3.mY; m33 = row3.mZ; m34 = row3.mW;
		m41 = row4.mX; m42 = row4.mY; m43 = row4.mZ; m44 = row4.mW;
	}

	Vector3 Matrix4x4::operator*(const Vector3& other) const
	{
		const f32 tempX = m11 * other.mX + m12 * other.mY + m13 * other.mZ;
		const f32 tempY = m21 * other.mX + m22 * other.mY + m23 * other.mZ;
		const f32 tempZ = m31 * other.mX + m32 * other.mY + m33 * other.mZ;

		return Vector3(tempX, tempY, tempZ);
	}

	Vector4 Matrix4x4::operator*(const Vector4& other) const
	{
		const f32 tempX = m11 * other.mX + m12 * other.mY + m13 * other.mZ + m14 * other.mW;
		const f32 tempY = m21 * other.mX + m22 * other.mY + m23 * other.mZ + m24 * other.mW;
		const f32 tempZ = m31 * other.mX + m32 * other.mY + m33 * other.mZ + m34 * other.mW;
		const f32 tempW = m41 * other.mW + m42 * other.mY + m43 * other.mZ + m44 * other.mW;

		return Vector4(tempX, tempY, tempZ, tempW);
	}

	Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other) const
	{
		const f32 _11 = m11 * other.m11 + m12 * other.m21 + m13 * other.m31 + m14 * other.m41;
		const f32 _12 = m11 * other.m12 + m12 * other.m22 + m13 * other.m32 + m14 * other.m42;
		const f32 _13 = m11 * other.m13 + m12 * other.m23 + m13 * other.m33 + m14 * other.m43;
		const f32 _14 = m11 * other.m14 + m12 * other.m24 + m13 * other.m34 + m14 * other.m44;

		const f32 _21 = m21 * other.m11 + m22 * other.m21 + m23 * other.m31 + m24 * other.m41;
		const f32 _22 = m21 * other.m12 + m22 * other.m22 + m23 * other.m32 + m24 * other.m42;
		const f32 _23 = m21 * other.m13 + m22 * other.m23 + m23 * other.m33 + m24 * other.m43;
		const f32 _24 = m21 * other.m14 + m22 * other.m24 + m23 * other.m34 + m24 * other.m44;

		const f32 _31 = m31 * other.m11 + m32 * other.m21 + m33 * other.m31 + m34 * other.m41;
		const f32 _32 = m31 * other.m12 + m32 * other.m22 + m33 * other.m32 + m34 * other.m42;
		const f32 _33 = m31 * other.m13 + m32 * other.m23 + m33 * other.m33 + m34 * other.m43;
		const f32 _34 = m31 * other.m14 + m32 * other.m24 + m33 * other.m34 + m34 * other.m44;

		const f32 _41 = m41 * other.m11 + m42 * other.m21 + m43 * other.m31 + m44 * other.m41;
		const f32 _42 = m41 * other.m12 + m42 * other.m22 + m43 * other.m32 + m44 * other.m42;
		const f32 _43 = m41 * other.m13 + m42 * other.m23 + m43 * other.m33 + m44 * other.m43;
		const f32 _44 = m41 * other.m14 + m42 * other.m24 + m43 * other.m34 + m44 * other.m44;

		return Matrix4x4(
			_11, _12, _13, _14,
			_21, _22, _23, _24,
			_31, _32, _33, _34,
			_41, _42, _43, _44
		);
	}

	Matrix4x4 Matrix4x4::operator*=(const Matrix4x4& other)
	{
		const f32 _11 = m11 * other.m11 + m12 * other.m21 + m13 * other.m31 + m14 * other.m41;
		const f32 _12 = m11 * other.m12 + m12 * other.m22 + m13 * other.m32 + m14 * other.m42;
		const f32 _13 = m11 * other.m13 + m12 * other.m23 + m13 * other.m33 + m14 * other.m43;
		const f32 _14 = m11 * other.m14 + m12 * other.m24 + m13 * other.m34 + m14 * other.m44;

		const f32 _21 = m21 * other.m11 + m22 * other.m21 + m23 * other.m31 + m24 * other.m41;
		const f32 _22 = m21 * other.m12 + m22 * other.m22 + m23 * other.m32 + m24 * other.m42;
		const f32 _23 = m21 * other.m13 + m22 * other.m23 + m23 * other.m33 + m24 * other.m43;
		const f32 _24 = m21 * other.m14 + m22 * other.m24 + m23 * other.m34 + m24 * other.m44;

		const f32 _31 = m31 * other.m11 + m32 * other.m21 + m33 * other.m31 + m34 * other.m41;
		const f32 _32 = m31 * other.m12 + m32 * other.m22 + m33 * other.m32 + m34 * other.m42;
		const f32 _33 = m31 * other.m13 + m32 * other.m23 + m33 * other.m33 + m34 * other.m43;
		const f32 _34 = m31 * other.m14 + m32 * other.m24 + m33 * other.m34 + m34 * other.m44;

		const f32 _41 = m41 * other.m11 + m42 * other.m21 + m43 * other.m31 + m44 * other.m41;
		const f32 _42 = m41 * other.m12 + m42 * other.m22 + m43 * other.m32 + m44 * other.m42;
		const f32 _43 = m41 * other.m13 + m42 * other.m23 + m43 * other.m33 + m44 * other.m43;
		const f32 _44 = m41 * other.m14 + m42 * other.m24 + m43 * other.m34 + m44 * other.m44;

		m11 = _11; m12 = _12; m13 = _13; m14 = _14;
		m21 = _21; m22 = _22; m23 = _23; m24 = _24;
		m31 = _31; m32 = _32; m33 = _33; m34 = _34;
		m41 = _41; m42 = _42; m43 = _43; m44 = _44;

		return Matrix4x4(
			_11, _12, _13, _14,
			_21, _22, _23, _24,
			_31, _32, _33, _34,
			_41, _42, _43, _44
		);
	}

	Matrix4x4 Matrix4x4::Transpose(const Matrix4x4& other)
	{
		return Matrix4x4(
			other.m11, other.m21, other.m31, other.m41,
			other.m12, other.m22, other.m32, other.m42,
			other.m13, other.m23, other.m33, other.m43,
			other.m14, other.m24, other.m34, other.m44);
	}

	void Matrix4x4::Transpose()
	{
		Math::Swap(m12, m21);
		Math::Swap(m13, m31);
		Math::Swap(m14, m41);
		Math::Swap(m23, m32);
		Math::Swap(m24, m42);
		Math::Swap(m34, m43);
	}

}
