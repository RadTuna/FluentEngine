
#include "Core/Allocator.h"


namespace Fluent
{

	StackAllocator::StackAllocator()
	{
		mStackLimit = 1048576;

		mMemoryStack = NewByArray<u8>(mStackLimit);
		mStackBottom = mMemoryStack;
		mStackTop = mMemoryStack + mStackLimit;
	}

	StackAllocator::StackAllocator(u32 stackLimit)
	{
		mStackLimit = stackLimit;

		mMemoryStack = NewByArray<u8>(mStackLimit);
		mStackBottom = mMemoryStack;
		mStackTop = mMemoryStack + mStackLimit;
	}

	StackAllocator::~StackAllocator()
	{
		mStackLimit = 0;

		DeleteByArray(mMemoryStack);
		mMemoryStack = nullptr;
		mStackBottom = nullptr;
		mStackTop = nullptr;
	}

}
