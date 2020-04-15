#pragma once

namespace Fluent
{

	inline void Assert(bool expression)
	{
#ifdef DEBUG
		assert(expression);
#else
		__assume(expression);
#endif
	}

	template<typename T>
	inline void MemSet(T* const dest, int value, u64 size)
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
	inline void MemCpy(T* const dest, U* const source, u64 size)
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
	inline void MemMove(T* const dest, U* const source, u64 size)
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
	inline T* New(Args&&... args)
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
	inline T* NewByArray(i32 size)
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
	inline void Delete(T* const object)
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
	inline void DeleteByArray(T* const object)
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

	inline u64 GenerateFID()
	{
		static u64 lastFID = 0;
		return lastFID++;
	}

	template<typename T>
	struct PointerRemover
	{
		using Type = T;
	};

	template<typename T>
	struct PointerRemover<T*>
	{
		using Type = T;
	};

}
