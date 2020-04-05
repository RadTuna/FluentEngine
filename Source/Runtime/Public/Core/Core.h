#pragma once

// External Include
#include <cassert>
#include <cstring>
#include <utility>
#include <cstdint>


// Type Def
#define FORCEINLINE __forceinline
#define INDEX_NONE		(-1)

using i8 = char;
using i16 = short;
using i32 = int;
using i64 = long long;

using u8 = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long long;

using f32 = float;
using f64 = double;

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
	FORCEINLINE void MemSet(T* const dest, int value, u64 size)
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
	FORCEINLINE void MemCpy(T* const dest, U* const source, u64 size)
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
	FORCEINLINE void MemMove(T* const dest, U* const source, u64 size)
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
	T* NewByArray(i32 size)
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

