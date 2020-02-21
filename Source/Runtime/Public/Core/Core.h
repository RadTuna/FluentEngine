#pragma once

// External Include
#include <cassert>
#include <cstring>
#include <utility>


// Type Def
#define FORCEINLINE __forceinline
#define SWITCH_FALLTHROUGH

using int8 = char;
using int16 = short;
using int32 = int;
using int64 = long long;

using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long long;

#define INT8_MIN         (-127i8 - 1)
#define INT16_MIN        (-32767i16 - 1)
#define INT32_MIN        (-2147483647i32 - 1)
#define INT64_MIN        (-9223372036854775807i64 - 1)
#define INT8_MAX         127i8
#define INT16_MAX        32767i16
#define INT32_MAX        2147483647i32
#define INT64_MAX        9223372036854775807i64
#define UINT8_MAX        0xffui8
#define UINT16_MAX       0xffffui16
#define UINT32_MAX       0xffffffffui32
#define UINT64_MAX       0xffffffffffffffffui64

#ifdef UNICODE
using gchar = wchar_t;
#else
using gchar = char;
#endif


// Core function
namespace Fluent
{

	FORCEINLINE void Assert(bool expression)
	{
#ifdef DEBUG
		assert(expression);
#else
		__assume(expression);
#endif
	}

	template<typename T>
	FORCEINLINE void MemSet(T* const dest, int value, uint64 size)
	{
#ifdef DEBUG
		if (dest != nullptr)
		{
			memset(dest, value, size);
		}
		else
		{
			Assert(false);
		}
#else
		memset(dest, value, size);
#endif
	}

	template<typename T, typename U>
	FORCEINLINE void MemCpy(T* const dest, U* const source, uint64 size)
	{
#ifdef DEBUG
		if (dest != nullptr && source != nullptr)
		{
			memcpy(dest, source, size);
		}
		else
		{
			Assert(false);
		}
#else
		mempy(dest, source, size);
#endif
	}

	template<typename T, typename U>
	FORCEINLINE void MemMove(T* const dest, U* const source, uint64 size)
	{
#ifdef DEBUG
		if (dest != nullptr && source != nullptr)
		{
			memmove(dest, source, size);
		}
		else
		{
			Assert(false);
		}
#else
		mempy(dest, source, size);
#endif
	}

	template<typename T, typename ...Args>
	T* New(Args&&... args)
	{
#ifdef DEBUG
		T* const NewObject = new T(args...);
		if (NewObject != nullptr)
		{
			return NewObject;
		}
		else
		{
			Assert(false);
			return nullptr;
		}
#else
		retrun new T(args...);
#endif
	}

	template<typename T>
	T* NewByArray(int32 size)
	{
#ifdef DEBUG
		T* const NewObject = new T[size];
		if (NewObject != nullptr)
		{
			return NewObject;
		}
		else
		{
			Assert(false);
			return nullptr;
		}
#else
		retrun new T[size];
#endif
	}

	template<typename T>
	void Delete(T* const object)
	{
#ifdef DEBUG
		if (object != nullptr)
		{
			delete object;
		}
		else
		{
			Assert(false);
		}
#else
		delete object;
#endif
	}

	template<typename T>
	void DeleteByArray(T* const object)
	{
#ifdef DEBUG
		if (object != nullptr)
		{
			delete[] object;
		}
		else
		{
			Assert(false);
		}
#else
		delete[] object;
#endif
	}

}

