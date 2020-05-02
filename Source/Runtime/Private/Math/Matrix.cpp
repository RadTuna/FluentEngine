
#include "Math/Matrix.h"
#include "Math/Vector.h"
#include "Math/Matrix4x4.h"


namespace Fluent
{

	const Matrix Matrix::Identity = Matrix(
		_mm_setr_ps(1.0f, 0.0f, 0.0f, 0.0f),
		_mm_setr_ps(0.0f, 1.0f, 0.0f, 0.0f),
		_mm_setr_ps(0.0f, 0.0f, 1.0f, 0.0f),
		_mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f));
	
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

	Matrix::Matrix(Vector inRow1, Vector inRow2, Vector inRow3, Vector inRow4) noexcept
		: mRow1(inRow1.mData)
		, mRow2(inRow2.mData)
		, mRow3(inRow3.mData)
		, mRow4(inRow4.mData)
	{
	}

	Matrix SIMD_CALL Matrix::operator=(Matrix other)
	{
		mRow1 = other.mRow1;
		mRow2 = other.mRow2;
		mRow3 = other.mRow3;
		mRow4 = other.mRow4;

		return Matrix(mRow1, mRow2, mRow3, mRow4);
	}

	Vector SIMD_CALL Matrix::operator*(Vector other) const
	{
		const Matrix tempMatrix = *this;

		const f32 tempX = DotSIMD(tempMatrix.mRow1, other.mData);
		const f32 tempY = DotSIMD(tempMatrix.mRow2, other.mData);
		const f32 tempZ = DotSIMD(tempMatrix.mRow3, other.mData);
		const f32 tempW = DotSIMD(tempMatrix.mRow4, other.mData);

		return Vector(_mm_setr_ps(tempX, tempY, tempZ, tempW));
	}

	Matrix SIMD_CALL Matrix::operator*(Matrix other) const
	{
		Matrix outMatrix;
		other.Transpose();

		f32 tempX = DotSIMD(mRow1, other.mRow1);
		f32 tempY = DotSIMD(mRow1, other.mRow2);
		f32 tempZ = DotSIMD(mRow1, other.mRow3);
		f32 tempW = DotSIMD(mRow1, other.mRow4);
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

	Matrix SIMD_CALL Matrix::operator*=(Matrix other)
	{
		f32 tempX = DotSIMD(mRow1, other.mRow1);
		f32 tempY = DotSIMD(mRow1, other.mRow2);
		f32 tempZ = DotSIMD(mRow1, other.mRow3);
		f32 tempW = DotSIMD(mRow1, other.mRow4);
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

	Matrix SIMD_CALL Matrix::Transpose(Matrix other)
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

	Matrix SIMD_CALL Matrix::CreateLookAtLH(Vector cameraPosition, Vector targetPosition, Vector upVector)
	{
		const Vector zAxis = Vector::Normalize(targetPosition - cameraPosition);
		const Vector xAxis = Vector::Normalize(Vector::CrossProduct(upVector, zAxis));
		const Vector yAxis = Vector::Normalize(Vector::CrossProduct(zAxis, xAxis));
		
		const Vector exAxis = Vector::SetVector4(
			-Vector::DotProduct(xAxis, cameraPosition),
			-Vector::DotProduct(yAxis, cameraPosition),
			-Vector::DotProduct(zAxis, cameraPosition),
			1.0f);
		
		Matrix outMatrix(xAxis, yAxis, zAxis, exAxis);
		outMatrix.Transpose();
		return outMatrix;
	}

	Matrix SIMD_CALL Matrix::CreateOrthographicLH(f32 width, f32 height, f32 near, f32 far)
	{
		const __m128 row1 = _mm_setr_ps(2.0f / width, 0.0f, 0.0f, 0.0f);
		const __m128 row2 = _mm_setr_ps(0.0f, 2.0f / height, 0.0f, 0.0f);
		const __m128 row3 = _mm_setr_ps(0.0f, 0.0f, 1.0f / (far - near), 0.0f);
		const __m128 row4 = _mm_setr_ps(0.0f, 0.0f, near / (near - far), 1.0f);

		return Matrix(row1, row2, row3, row4);
	}

	Matrix SIMD_CALL Matrix::CreatePerspectiveLH(f32 width, f32 height, f32 near, f32 far)
	{
		const f32 aspectRatio = height / width;
		const f32 fov = atan2(height * 0.5f, near) * 2.0f;

		return CreatePerspectiveFovLH(fov, aspectRatio, near, far);
	}

	Matrix SIMD_CALL Matrix::CreatePerspectiveFovLH(f32 fov, f32 aspectRatio, f32 near, f32 far)
	{
		const f32 yScale = 1.0f / (fov * 0.5f);
		const f32 xScale = yScale / aspectRatio;

		const __m128 row1 = _mm_setr_ps(xScale, 0.0f, 0.0f, 0.0f);
		const __m128 row2 = _mm_setr_ps(0.0f, yScale, 0.0f, 0.0f);
		const __m128 row3 = _mm_setr_ps(0.0f, 0.0f, far / (far - near), 1.0f);
		const __m128 row4 = _mm_setr_ps(0.0f, 0.0f, -near * far / (far - near), 0.0f);

		return Matrix(row1, row2, row3, row4);
	}

	Matrix SIMD_CALL Matrix::LoadMatrix4X4(const Matrix4x4& inMatrix)
	{
		return Matrix(
			_mm_setr_ps(inMatrix.m11, inMatrix.m12, inMatrix.m13, inMatrix.m14),
			_mm_setr_ps(inMatrix.m21, inMatrix.m22, inMatrix.m23, inMatrix.m24),
			_mm_setr_ps(inMatrix.m31, inMatrix.m32, inMatrix.m33, inMatrix.m34),
			_mm_setr_ps(inMatrix.m41, inMatrix.m42, inMatrix.m43, inMatrix.m44));
	}

	void SIMD_CALL Matrix::StoreMatrix4X4(Matrix inMatrix, Matrix4x4* outMatrix)
	{
		FloatVector tempVector1 = {};
		FloatVector tempVector2 = {};
		FloatVector tempVector3 = {};
		FloatVector tempVector4 = {};

		_mm_store_ps(tempVector1.Data, inMatrix.mRow1);
		_mm_store_ps(tempVector2.Data, inMatrix.mRow2);
		_mm_store_ps(tempVector3.Data, inMatrix.mRow3);
		_mm_store_ps(tempVector4.Data, inMatrix.mRow4);

		outMatrix->m11 = tempVector1.X;
		outMatrix->m12 = tempVector1.Y;
		outMatrix->m13 = tempVector1.Z;
		outMatrix->m14 = tempVector1.W;

		outMatrix->m21 = tempVector2.X;
		outMatrix->m22 = tempVector2.Y;
		outMatrix->m23 = tempVector2.Z;
		outMatrix->m24 = tempVector2.W;

		outMatrix->m31 = tempVector3.X;
		outMatrix->m32 = tempVector3.Y;
		outMatrix->m33 = tempVector3.Z;
		outMatrix->m34 = tempVector3.W;

		outMatrix->m41 = tempVector4.X;
		outMatrix->m42 = tempVector4.Y;
		outMatrix->m43 = tempVector4.Z;
		outMatrix->m44 = tempVector4.W;
	}

	f32 SIMD_CALL Matrix::DotSIMD(__m128 vector1, __m128 vector2)
	{
		const __m128 mulData = _mm_mul_ps(vector1, vector2);
		const __m128 tempAddData = _mm_hadd_ps(mulData, mulData);
		const __m128 outData = _mm_hadd_ps(tempAddData, tempAddData);

		return _mm_cvtss_f32(outData);
	}

}
