#pragma once

#include "Core/Core.h"

namespace Fluent
{

	class StackAllocator
	{
	public:

		explicit StackAllocator();
		explicit StackAllocator(uint32 stackLimit);

		StackAllocator(const StackAllocator& other) = delete;
		StackAllocator(StackAllocator&& other) = delete;
		StackAllocator& operator=(const StackAllocator& other) = delete;

		~StackAllocator();

	public:

		template <typename T, typename ... Args>
		friend T* NewStack(StackAllocator& memStack, Args... args);

		template <typename T>
		friend void DeleteStack(StackAllocator& memStack, T* object);

		template <typename T>
		friend T* NewStackByArray(StackAllocator& memStack, int32 size);

		template <typename T>
		friend void DeleteStackByArray(StackAllocator& memStack, T* object, int32 size);

	private:

		uint8* mMemoryStack;
		uint8* mStackBottom;
		uint8* mStackTop;

		uint32 mStackLimit;

	};


	template <typename T, typename ... Args>
	T* NewStack(StackAllocator& memStack, Args... args)
	{
		const uint32 objectSize = sizeof(T);
		if (memStack.mStackTop < memStack.mStackBottom + objectSize)
		{
			return nullptr;
		}

		T newObject(args...);

		uint8* convertPtr = reinterpret_cast<uint8*>(&newObject);
		for (uint32 index = 0; index < objectSize; ++index)
		{
			memStack.mStackBottom[index] = convertPtr[index];
		}

		uint8* stackBottomCache = memStack.mStackBottom;
		memStack.mStackBottom += objectSize;

		return reinterpret_cast<T*>(stackBottomCache);
	}

	template <typename T>
	void DeleteStack(StackAllocator& memStack, T* object)
	{
		if (!object)
		{
			return;
		}

		const uint32 objectSize = sizeof(T);
		uint8* convertPtr = reinterpret_cast<uint8*>(object);
		if (convertPtr == memStack.mStackBottom - objectSize)
		{
			memStack.mStackBottom -= objectSize;
			for (uint32 index = 0; index < objectSize; ++index)
			{
				memStack.mStackBottom[index] = 0;
			}
		}
		else
		{
			Assert(false);
		}
	}

	template <typename T>
	T* NewStackByArray(StackAllocator& memStack, int32 size)
	{
		const uint32 objectSize = sizeof(T);
		if (memStack.mStackTop < memStack.mStackBottom + (objectSize * size))
		{
			return nullptr;
		}

		uint8* stackBottomCache = memStack.mStackBottom;
		for (int32 arrayIndex = 0; arrayIndex < size; ++arrayIndex)
		{
			T newObject = T();

			uint8* convertPtr = reinterpret_cast<uint8*>(&newObject);
			for (uint32 index = 0; index < objectSize; ++index)
			{
				memStack.mStackBottom[index] = convertPtr[index];
			}

			memStack.mStackBottom += objectSize;
		}

		return reinterpret_cast<T*>(stackBottomCache);
	}

	template <typename T>
	void DeleteStackByArray(StackAllocator& memStack, T* object, int32 size)
	{
		if (!object)
		{
			return;
		}

		const uint32 objectSize = sizeof(T);
		uint8* convertPtr = reinterpret_cast<uint8*>(object);
		if (convertPtr == memStack.mStackBottom - (objectSize * size))
		{
			memStack.mStackBottom -= objectSize * size;
			const uint32 indexEnd = objectSize * size;
			for (uint32 index = 0; index < indexEnd; ++index)
			{
				memStack.mStackBottom[index] = 0;
			}
		}
		else
		{
			Assert(false);
		}
	}

}

