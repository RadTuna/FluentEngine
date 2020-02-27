#pragma once


namespace Fluent
{
	class Vector3;
	class Vector4;
	
	class Quaternion
	{
	public:

		// Real number
		float mR;

		// Image number
		float mI;
		float mJ;
		float mK;

	public:


		Quaternion operator+(const Quaternion& other);
		Quaternion operator+=(const Quaternion& other);

		Quaternion operator-(const Quaternion& other);
		Quaternion operator-=(const Quaternion& other);

		Quaternion operator*(const Quaternion& other);
		Quaternion operator*=(const Quaternion& other);

		Vector3 Rotate(const Vector3& other);
		Vector4 Rotate(const Vector4& other);

		void SetEuler(const Vector3& other);

		[[nodiscard]]
		Vector3 ToEuler() const;
		
		[[nodiscard]]
		float Length() const;

	};

}
