
#include "Math/Vector.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Matrix.h"


namespace Fluent
{

	Vector::Vector() noexcept
	{
		mData = _mm_setzero_ps();
	}

	Vector __vectorcall Vector::operator=(Vector other)
	{
		mData = other.mData;
		return Vector(mData);
	}

	Vector __vectorcall Vector::operator=(__m128 other)
	{
		mData = other;
		return Vector(mData);
	}

	Vector __vectorcall Vector::operator+(Vector other) const
	{
		return Vector(_mm_add_ps(mData, other.mData));
	}

	Vector __vectorcall Vector::operator+=(Vector other)
	{
		mData = _mm_add_ps(mData, other.mData);
		return Vector(mData);
	}

	Vector __vectorcall Vector::operator-(Vector other) const
	{
		return Vector(_mm_sub_ps(mData, other.mData));
	}

	Vector __vectorcall Vector::operator-=(Vector other)
	{
		mData = _mm_sub_ps(mData, other.mData);
		return Vector(_mm_sub_ps(mData, other.mData));
	}

	Vector __vectorcall Vector::operator*(float other) const
	{
		const __m128 multiplier = _mm_set_ps1(other);
		return Vector(_mm_mul_ps(mData, multiplier));
	}

	Vector __vectorcall Vector::operator*=(float other)
	{
		const __m128 multiplier = _mm_set_ps1(other);
		mData = _mm_mul_ps(mData, multiplier);
		return Vector(mData);
	}

	float __vectorcall Vector::operator*(Vector other) const
	{
		const __m128 mulData = _mm_mul_ps(mData, other.mData);
		const __m128 tempAddData = _mm_hadd_ps(mulData, mulData);
		const __m128 outData = _mm_hadd_ps(tempAddData, tempAddData);

		return _mm_cvtss_f32(outData);
	}

	Vector Vector::operator*(Matrix other) const
	{
		other.Transpose();

		const float tempX = Matrix::DotSIMD(other.mRow1, mData);
		const float tempY = Matrix::DotSIMD(other.mRow2, mData);
		const float tempZ = Matrix::DotSIMD(other.mRow3, mData);
		const float tempW = Matrix::DotSIMD(other.mRow4, mData);
		const __m128 outData = _mm_set_ps(tempX, tempY, tempZ, tempW);

		return Vector(outData);
	}

	Vector Vector::operator*=(Matrix other)
	{
		other.Transpose();

		const float tempX = Matrix::DotSIMD(other.mRow1, mData);
		const float tempY = Matrix::DotSIMD(other.mRow2, mData);
		const float tempZ = Matrix::DotSIMD(other.mRow3, mData);
		const float tempW = Matrix::DotSIMD(other.mRow4, mData);
		mData = _mm_set_ps(tempX, tempY, tempZ, tempW);

		return Vector(mData);
	}

	Vector __vectorcall Vector::operator^(Vector other) const
	{
		__m128 otherTempData = _mm_shuffle_ps(other.mData, other.mData, _MM_SHUFFLE(3, 0, 2, 1));
		__m128 myTempData = _mm_shuffle_ps(mData, mData, _MM_SHUFFLE(3, 0, 2, 1));
		otherTempData = _mm_mul_ps(otherTempData, mData);
		myTempData = _mm_mul_ps(myTempData, other.mData);
		const __m128 tempSubData = _mm_sub_ps(otherTempData, myTempData);
		const __m128 outData = _mm_shuffle_ps(tempSubData, tempSubData, _MM_SHUFFLE(3, 0, 2, 1));

		return Vector(outData);
	}

	float Vector::DotProduct(Vector vectorA, Vector vectorB)
	{
		return vectorA * vectorB;
	}

	Vector Vector::CrossProduct(Vector vectorA, Vector vectorB)
	{
		return vectorA ^ vectorB;
	}

	float __vectorcall Vector::Length() const
	{
		const __m128 tempMulData = _mm_mul_ps(mData, mData);
		__m128 tempAddData = _mm_hadd_ps(tempMulData, tempMulData);
		tempAddData = _mm_hadd_ps(tempAddData, tempAddData);
		const __m128 outData = _mm_sqrt_ps(tempAddData);

		return _mm_cvtss_f32(outData);
	}

	Vector __vectorcall Vector::Normalize(Vector other)
	{
		const __m128 tempMulData = _mm_mul_ps(other.mData, other.mData);
		__m128 tempAddData = _mm_hadd_ps(tempMulData, tempMulData);
		tempAddData = _mm_hadd_ps(tempAddData, tempAddData);
		const __m128 sizeData = _mm_sqrt_ps(tempAddData);
		const __m128 outData = _mm_div_ps(other.mData, sizeData);

		return Vector(outData);
	}

	void Vector::Normalize()
	{
		const __m128 tempMulData = _mm_mul_ps(mData, mData);
		__m128 tempAddData = _mm_hadd_ps(tempMulData, tempMulData);
		tempAddData = _mm_hadd_ps(tempAddData, tempAddData);
		const __m128 sizeData = _mm_sqrt_ps(tempAddData);

		mData = _mm_div_ps(mData, sizeData);
	}

	Vector __vectorcall Vector::LoadVector3(const Vector3& inVector)
	{
		return Vector(_mm_setr_ps(inVector.mX, inVector.mY, inVector.mZ, 0.0f));
	}

	Vector __vectorcall Vector::LoadVector4(const Vector4& inVector)
	{
		return Vector(_mm_setr_ps(inVector.mX, inVector.mY, inVector.mZ, inVector.mW));
	}

	void __vectorcall Vector::StoreVector3(Vector inVector, Vector3* outVector)
	{
		FloatVector tempVector = {};
		_mm_store_ps(tempVector.Data, inVector.mData);

		outVector->mX = tempVector.X;
		outVector->mY = tempVector.Y;
		outVector->mZ = tempVector.Z;
	}

	void __vectorcall Vector::StoreVector4(Vector inVector, Vector4* outVector)
	{
		FloatVector tempVector = {};
		_mm_store_ps(tempVector.Data, inVector.mData);

		outVector->mX = tempVector.X;
		outVector->mY = tempVector.Y;
		outVector->mZ = tempVector.Z;
		outVector->mW = tempVector.W;
	}

	Vector Vector::SetVector3(float x, float y, float z)
	{
		return Vector(_mm_setr_ps(x, y, z, 0.0f));
	}

	Vector Vector::SetVector4(float x, float y, float z, float w)
	{
		return Vector(_mm_setr_ps(x, y, z, w));
	}

	Vector __vectorcall Fluent::operator*(float other, Vector thisVector)
	{
		const __m128 multiplier = _mm_set_ps1(other);
		return Vector(_mm_mul_ps(thisVector.mData, multiplier));
	}

}
