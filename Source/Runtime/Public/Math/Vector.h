#pragma once

// External Include
#include <intrin.h> // common intrinsic
#include <xmmintrin.h> // SSE intrinsic
#include <emmintrin.h> // SSE2 intrinsic
#include <pmmintrin.h> // SSE3 intrinsic


namespace Fluent
{

	union __declspec(align(16)) FloatVector
	{
		struct
		{
			float X;
			float Y;
			float Z;
			float W;
		};

		float Data[4];
	};

	class Vector
	{
	public:

		__m128 mData;

	public:

		explicit Vector() noexcept;
		explicit constexpr __fastcall Vector(__m128 initData) noexcept : mData(initData) {}

		~Vector() = default;

		Vector __vectorcall operator=(const Vector& other) = delete;
		Vector __vectorcall operator=(Vector other);
		Vector __vectorcall operator=(__m128 other);

		Vector __vectorcall operator+(Vector other) const;
		Vector __vectorcall operator+=(Vector other);

		Vector __vectorcall operator-(Vector other) const;
		Vector __vectorcall operator-=(Vector other);

		Vector __vectorcall operator*(float other) const;
		Vector __vectorcall operator*=(float other);

		Vector __vectorcall operator*(Vector other) const;

		Vector __vectorcall operator^(Vector other) const;

		static Vector __vectorcall DotProduct(Vector vectorA, Vector vectorB);

		static Vector __vectorcall CrossProduct(Vector vectorA, Vector vectorB);

		Vector __vectorcall Size() const;

		static Vector __vectorcall Normalize(Vector other);
		void Normalize();

		static Vector __vectorcall LoadVector3(const class Vector3& inVector);
		static Vector __vectorcall LoadVector4(const class Vector4& inVector);

		static void __vectorcall StoreVector3(Vector inVector, class Vector3* outVector);
		static void __vectorcall StoreVector4(Vector inVector, class Vector4* outVector);

		static Vector __vectorcall SetVector3(float x, float y, float z);
		static Vector __vectorcall SetVector4(float x, float y, float z, float w);

		static const Vector ZeroVector;
		static const Vector OneVector;
		static const Vector UnitX;
		static const Vector UnitY;
		static const Vector UnitZ;

	};

}
