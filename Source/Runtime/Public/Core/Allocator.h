#pragma once

#include "Core/Core.h"

namespace ConstexprAllocator
{
	constexpr uint32 StackLimit = 10485760;
	constexpr uint32 PoolLimit = 10485760;
}

class Allocator
{
public:
	
	template<typename T, typename ...Args>
	static T* NewStack(Args... args)
	{
		const uint32 objectSize = sizeof(T);
		if (mStackTop < mStackBottom + objectSize)
		{
			return nullptr;
		}
		
		T newObject(args...);
		
		uint8* convertPtr = reinterpret_cast<uint8*>(&newObject);
		for (uint32 index = 0; index < objectSize; ++index)
		{
			mStackBottom[index] = convertPtr[index];
		}

		uint8* stackBottomCache = mStackBottom;
		mStackBottom += objectSize;

		return reinterpret_cast<T*>(stackBottomCache);
	}

	template<typename T>
	static void DeleteStack(T* object)
	{
		if (!object)
		{
			return;
		}

		const uint32 objectSize = sizeof(T);
		uint8* convertPtr = reinterpret_cast<uint8*>(object);
		if (convertPtr == mStackBottom - objectSize)
		{
			mStackBottom -= objectSize;
			for (uint32 index = 0; index < objectSize; ++index)
			{
				mStackBottom[index] = 0;
			}
		}
		else
		{
			Fluent::Assert(false);
		}
	}

	template<typename T>
	static T* NewStackByArray(int32 size)
	{
		const uint32 objectSize = sizeof(T);
		if (mStackTop < mStackBottom + (objectSize * size))
		{
			return nullptr;
		}

		uint8* stackBottomCache = mStackBottom;
		for (int32 arrayIndex = 0; arrayIndex < size; ++arrayIndex)
		{
			T newObject = T();

			uint8* convertPtr = reinterpret_cast<uint8*>(&newObject);
			for (uint32 index = 0; index < objectSize; ++index)
			{
				mStackBottom[index] = convertPtr[index];
			}

			mStackBottom += objectSize;
		}

		return reinterpret_cast<T*>(stackBottomCache);
	}

	template<typename T>
	static void DeleteStackByArray(T* object, int32 size)
	{
		if (!object)
		{
			return;
		}

		const uint32 objectSize = sizeof(T);
		uint8* convertPtr = reinterpret_cast<uint8*>(object);
		if (convertPtr == mStackBottom - (objectSize * size))
		{
			mStackBottom -= objectSize * size;
			const uint32 indexEnd = objectSize * size;
			for (uint32 index = 0; index < indexEnd; ++index)
			{
				mStackBottom[index] = 0;
			}
		}
		else
		{
			Fluent::Assert(false);
		}
	}

private:

	inline static uint8* mMemoryStack = Fluent::NewByArray<uint8>(ConstexprAllocator::StackLimit); // 10MB
	inline static uint8* mStackBottom = mMemoryStack;
	inline static uint8* mStackTop = mMemoryStack + ConstexprAllocator::StackLimit;
	
};
