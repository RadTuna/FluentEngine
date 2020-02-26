
#include "Math/Vector.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"


using namespace Fluent;

const Vector Vector::ZeroVector(_mm_setzero_ps());
const Vector Vector::OneVector(_mm_set_ps1(1.0f));
const Vector Vector::UnitX = SetVector3(1.0f, 0.0f, 0.0f);
const Vector Vector::UnitY = SetVector3(0.0f, 1.0f, 0.0f);
const Vector Vector::UnitZ = SetVector3(0.0f, 0.0f, 1.0f);

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

Vector __vectorcall Vector::operator*(Vector other) const
{
	const __m128 mulData = _mm_mul_ps(mData, other.mData);
	const __m128 tempAddData = _mm_hadd_ps(mulData, mulData);
	const __m128 outData = _mm_hadd_ps(tempAddData, tempAddData);
	
	return Vector(outData);
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

Vector Vector::DotProduct(Vector vectorA, Vector vectorB)
{
	return vectorA * vectorB;
}

Vector Vector::CrossProduct(Vector vectorA, Vector vectorB)
{
	return vectorA ^ vectorB;
}

Vector __vectorcall Vector::Size() const
{
	const __m128 tempMulData = _mm_mul_ps(mData, mData);
	__m128 tempAddData = _mm_hadd_ps(tempMulData, tempMulData);
	tempAddData = _mm_hadd_ps(tempAddData, tempAddData);
	const __m128 outData = _mm_sqrt_ps(tempAddData);

	return Vector(outData);
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
	return Vector(_mm_set_ps(0.0f, inVector.mZ, inVector.mY, inVector.mX));
}

Vector __vectorcall Vector::LoadVector4(const Vector4& inVector)
{
	return Vector(_mm_set_ps(inVector.mW, inVector.mZ, inVector.mY, inVector.mX));
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
	return Vector(_mm_set_ps(0.0f, z, y, x));
}

Vector Vector::SetVector4(float x, float y, float z, float w)
{
	return Vector(_mm_set_ps(w, z, y, x));
}
