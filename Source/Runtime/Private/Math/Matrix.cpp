
#include "Math/Matrix.h"
#include "Math/Vector.h"


using namespace Fluent;

Matrix::Matrix() noexcept
{
	mRow1 = _mm_setzero_ps();
	mRow2 = _mm_setzero_ps();
	mRow3 = _mm_setzero_ps();
	mRow4 = _mm_setzero_ps();
}

Matrix::Matrix(const __m128& inRow1, const __m128& inRow2, const __m128& inRow3, const __m128& inRow4) noexcept
	: mRow1(inRow1)
	, mRow2(inRow2)
	, mRow3(inRow3)
	, mRow4(inRow4)
{
}

Matrix Matrix::operator=(Matrix other)
{
	mRow1 = other.mRow1;
	mRow2 = other.mRow2;
	mRow3 = other.mRow3;
	mRow4 = other.mRow4;

	return Matrix(mRow1, mRow2, mRow3, mRow4);
}

Vector Matrix::operator*(Vector other) const
{
	const Matrix tempMatrix = *this;
	
	const float tempX = DotSIMD(tempMatrix.mRow1, other.mData);
	const float tempY = DotSIMD(tempMatrix.mRow2, other.mData);
	const float tempZ = DotSIMD(tempMatrix.mRow3, other.mData);
	const float tempW = DotSIMD(tempMatrix.mRow4, other.mData);

	return Vector(_mm_setr_ps(tempX, tempY, tempZ, tempW));
}

Matrix Matrix::operator*(Matrix other) const
{
	Matrix outMatrix;
	other.Transpose();

	float tempX = DotSIMD(mRow1, other.mRow1);
	float tempY = DotSIMD(mRow1, other.mRow2);
	float tempZ = DotSIMD(mRow1, other.mRow3);
	float tempW = DotSIMD(mRow1, other.mRow4);
	outMatrix.mRow1 = _mm_setr_ps(tempX, tempY, tempZ, tempW);

	tempX = DotSIMD(mRow2, other.mRow1);
	tempY = DotSIMD(mRow2, other.mRow2);
	tempZ = DotSIMD(mRow2, other.mRow3);
	tempW = DotSIMD(mRow2, other.mRow4);
	outMatrix.mRow2 = _mm_setr_ps(tempX, tempY, tempZ, tempW);

	tempX = DotSIMD(mRow3, other.mRow1);
	tempY = DotSIMD(mRow3, other.mRow2);
	tempZ = DotSIMD(mRow3, other.mRow3);
	tempW = DotSIMD(mRow3, other.mRow4);
	outMatrix.mRow3 = _mm_setr_ps(tempX, tempY, tempZ, tempW);

	tempX = DotSIMD(mRow4, other.mRow1);
	tempY = DotSIMD(mRow4, other.mRow2);
	tempZ = DotSIMD(mRow4, other.mRow3);
	tempW = DotSIMD(mRow4, other.mRow4);
	outMatrix.mRow4 = _mm_setr_ps(tempX, tempY, tempZ, tempW);

	return outMatrix;
}

Matrix Matrix::operator*=(Matrix other)
{
	float tempX = DotSIMD(mRow1, other.mRow1);
	float tempY = DotSIMD(mRow1, other.mRow2);
	float tempZ = DotSIMD(mRow1, other.mRow3);
	float tempW = DotSIMD(mRow1, other.mRow4);
	mRow1 = _mm_setr_ps(tempX, tempY, tempZ, tempW);

	tempX = DotSIMD(mRow2, other.mRow1);
	tempY = DotSIMD(mRow2, other.mRow2);
	tempZ = DotSIMD(mRow2, other.mRow3);
	tempW = DotSIMD(mRow2, other.mRow4);
	mRow2 = _mm_setr_ps(tempX, tempY, tempZ, tempW);

	tempX = DotSIMD(mRow3, other.mRow1);
	tempY = DotSIMD(mRow3, other.mRow2);
	tempZ = DotSIMD(mRow3, other.mRow3);
	tempW = DotSIMD(mRow3, other.mRow4);
	mRow3 = _mm_setr_ps(tempX, tempY, tempZ, tempW);

	tempX = DotSIMD(mRow4, other.mRow1);
	tempY = DotSIMD(mRow4, other.mRow2);
	tempZ = DotSIMD(mRow4, other.mRow3);
	tempW = DotSIMD(mRow4, other.mRow4);
	mRow4 = _mm_setr_ps(tempX, tempY, tempZ, tempW);

	return Matrix(mRow1, mRow2, mRow3, mRow4);
}

Matrix Matrix::Transpose(Matrix other)
{
	const __m128 tempRow1 = _mm_unpacklo_ps(other.mRow1, other.mRow2);
	const __m128 tempRow2 = _mm_unpacklo_ps(other.mRow3, other.mRow4);
	const __m128 tempRow3 = _mm_unpackhi_ps(other.mRow1, other.mRow2);
	const __m128 tempRow4 = _mm_unpackhi_ps(other.mRow3, other.mRow4);

	const __m128 outRow1 = _mm_movelh_ps(tempRow1, tempRow2);
	const __m128 outRow2 = _mm_movehl_ps(tempRow1, tempRow2);
	const __m128 outRow3 = _mm_movelh_ps(tempRow3, tempRow4);
	const __m128 outRow4 = _mm_movehl_ps(tempRow3, tempRow4);

	return Matrix(outRow1, outRow2, outRow3, outRow4);
}

void Matrix::Transpose()
{
	const __m128 tempRow1 = _mm_unpacklo_ps(mRow1, mRow2);
	const __m128 tempRow2 = _mm_unpacklo_ps(mRow3, mRow4);
	const __m128 tempRow3 = _mm_unpackhi_ps(mRow1, mRow2);
	const __m128 tempRow4 = _mm_unpackhi_ps(mRow3, mRow4);

	mRow1 = _mm_movelh_ps(tempRow1, tempRow2);
	mRow2 = _mm_movehl_ps(tempRow1, tempRow2);
	mRow3 = _mm_movelh_ps(tempRow3, tempRow4);
	mRow4 = _mm_movehl_ps(tempRow3, tempRow4);
}

Matrix Matrix::LoadMatrix4X4(const Matrix4x4& inMatrix)
{
}

void Matrix::StoreMatrix4X4(Matrix inMatrix, Matrix4x4* outMatrix)
{
}

float Matrix::DotSIMD(__m128 vector1, __m128 vector2)
{
	const __m128 mulData = _mm_mul_ps(vector1, vector2);
	const __m128 tempAddData = _mm_hadd_ps(mulData, mulData);
	const __m128 outData = _mm_hadd_ps(tempAddData, tempAddData);

	return _mm_cvtss_f32(outData);
}
