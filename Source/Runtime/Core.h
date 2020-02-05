#pragma once

#include <cassert>
#include <cstring>
#include "DataTypeDefinition.h"

#define FORCEINLINE __forceinline

namespace FluentEngine
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
	T* New(Args... args)
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


