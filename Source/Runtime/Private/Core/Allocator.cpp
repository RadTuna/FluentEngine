
#include "Core/Allocator.h"


namespace Fluent
{

	StackAllocator gStackAllocator;

	StackAllocator::StackAllocator()
	{
		mStackLimit = DEFAULT_STACK_LIMIT;

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
