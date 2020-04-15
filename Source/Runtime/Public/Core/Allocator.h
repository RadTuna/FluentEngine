#pragma once

#include "Core/Core.h"

namespace Fluent
{
	
	constexpr u32 DEFAULT_STACK_LIMIT = 1048576;
	
	class StackAllocator
	{
	public:

		explicit StackAllocator();
		explicit StackAllocator(u32 stackLimit);

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
		friend T* NewStackByArray(StackAllocator& memStack, u32 size);

		template <typename T>
		friend void DeleteStackByArray(StackAllocator& memStack, T* object, u32 size);

	private:

		u8* mMemoryStack;
		u8* mStackBottom;
		u8* mStackTop;

		u32 mStackLimit;

	};

	extern StackAllocator gStackAllocator;

	template <typename T, typename ... Args>
	T* NewStack(StackAllocator& memStack, Args... args)
	{
		const u32 objectSize = static_cast<u32>(sizeof(T));
		if (memStack.mStackTop < memStack.mStackBottom + objectSize)
		{
			return nullptr;
		}

		T newObject(args...);

		u8* convertPtr = reinterpret_cast<u8*>(&newObject);
		MemCpy(memStack.mStackBottom, convertPtr, objectSize);

		u8* stackBottomCache = memStack.mStackBottom;
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

		const u32 objectSize = static_cast<u32>(sizeof(T));
		u8* convertPtr = reinterpret_cast<u8*>(object);
		if (convertPtr == memStack.mStackBottom - objectSize)
		{
			memStack.mStackBottom -= objectSize;
			MemSet(memStack.mStackBottom, 0, objectSize);
		}
		else
		{
			Assert(false);
		}
	}

	template <typename T>
	T* NewStackByArray(StackAllocator& memStack, u32 size)
	{
		const u32 objectSize = static_cast<u32>(sizeof(T));
		if (memStack.mStackTop < memStack.mStackBottom + (objectSize * size))
		{
			return nullptr;
		}

		u8* stackBottomCache = memStack.mStackBottom;
		for (u32 arrayIndex = 0; arrayIndex < size; ++arrayIndex)
		{
			T newObject = T();

			u8* convertPtr = reinterpret_cast<u8*>(&newObject);
			MemCpy(memStack.mStackBottom, convertPtr, objectSize);

			memStack.mStackBottom += objectSize;
		}

		return reinterpret_cast<T*>(stackBottomCache);
	}

	template <typename T>
	void DeleteStackByArray(StackAllocator& memStack, T* object, u32 size)
	{
		if (!object)
		{
			return;
		}

		const u32 objectSize = static_cast<u32>(sizeof(T));
		u8* convertPtr = reinterpret_cast<u8*>(object);
		if (convertPtr == memStack.mStackBottom - (objectSize * size))
		{
			const u32 totalSize = objectSize * size;
			memStack.mStackBottom -= totalSize;
			MemSet(memStack.mStackBottom, 0, totalSize);
		}
		else
		{
			Assert(false);
		}
	}

}

