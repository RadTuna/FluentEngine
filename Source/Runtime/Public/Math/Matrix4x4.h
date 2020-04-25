#pragma once

// Engine Include
#include "Core/TypeDefinition.h"
#include "Matrix.h"


namespace Fluent
{

	class Vector3;
	class Vector4;
	
	class Matrix4x4 final
	{
	public:

		f32 m11, m12, m13, m14;
		f32 m21, m22, m23, m24;
		f32 m31, m32, m33, m34;
		f32 m41, m42, m43, m44;

	public:

		explicit Matrix4x4() = default;
		explicit constexpr Matrix4x4(
			f32 _11, f32 _12, f32 _13, f32 _14,
			f32 _21, f32 _22, f32 _23, f32 _24,
			f32 _31, f32 _32, f32 _33, f32 _34,
			f32 _41, f32 _42, f32 _43, f32 _44) noexcept;
		explicit Matrix4x4(const Vector4& row1, const Vector4& row2, const Vector4& row3, const Vector4& row4) noexcept;

		~Matrix4x4() = default;

		Vector3 operator*(const Vector3& other) const;
		
		Vector4 operator*(const Vector4& other) const;

		Matrix4x4 operator*(const Matrix4x4& other) const;
		Matrix4x4 operator*=(const Matrix4x4& other);

		static Matrix4x4 Transpose(const Matrix4x4& other);
		void Transpose();

	};

	constexpr Matrix4x4::Matrix4x4(
		f32 _11, f32 _12, f32 _13, f32 _14,
		f32 _21, f32 _22, f32 _23, f32 _24, 
		f32 _31, f32 _32, f32 _33, f32 _34, 
		f32 _41, f32 _42, f32 _43, f32 _44) noexcept
		: m11(_11), m12(_12), m13(_13), m14(_14)
		, m21(_21), m22(_22), m23(_23), m24(_24)
		, m31(_31), m32(_32), m33(_33), m34(_34)
		, m41(_41), m42(_42), m43(_43), m44(_44)
	{
	}
}
