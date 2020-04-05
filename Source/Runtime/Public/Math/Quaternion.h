#pragma once

// Engine Include
#include "Core/Core.h"


namespace Fluent
{
	class Vector3;
	class Vector4;
	class Matrix4x4;
	
	class Quaternion final
	{
	public:

		// Real number
		f32 mR;

		// Image number
		f32 mI;
		f32 mJ;
		f32 mK;

	public:

		explicit Quaternion() = default;
		explicit constexpr Quaternion(f32 r, f32 i, f32 j, f32 k) noexcept;
		explicit Quaternion(const Vector3& eulerAngle) noexcept;
		explicit Quaternion(const Vector4& eulerAngle) noexcept;

		Quaternion operator+(const Quaternion& other) const;
		Quaternion operator+=(const Quaternion& other);

		Quaternion operator-(const Quaternion& other) const;
		Quaternion operator-=(const Quaternion& other);

		Quaternion operator*(const Quaternion& other) const;
		Quaternion operator*=(const Quaternion& other);

		Vector3 Rotate(const Vector3& other);
		Vector4 Rotate(const Vector4& other);

		void SetEuler(const Vector3& other);
		void SetEuler(const Vector4& other);

		[[nodiscard]]
		Vector3 ToEuler() const;

		[[nodiscard]]
		Vector4 ToEuler4() const;

		[[nodiscard]]
		Matrix4x4 ToMatrix() const;

		[[nodiscard]]
		Quaternion ToConjugate() const;
		
		[[nodiscard]]
		f32 Length() const;

		static Quaternion Normalize(const Quaternion& other);
		void Normalize();

		static const Quaternion Identity;

	};

	constexpr Quaternion::Quaternion(f32 r, f32 i, f32 j, f32 k) noexcept
		: mR(r)
		, mI(i)
		, mJ(j)
		, mK(k)
	{
	}
}
