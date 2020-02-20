
#include "Core/Allocator.h"

using namespace Fluent;

StackAllocator::StackAllocator()
{
	mStackLimit = 1048576;
	
	mMemoryStack = NewByArray<uint8>(mStackLimit);
	mStackBottom = mMemoryStack;
	mStackTop = mMemoryStack + mStackLimit;
}

StackAllocator::StackAllocator(uint32 stackLimit)
{
	mStackLimit = stackLimit;

	mMemoryStack = NewByArray<uint8>(mStackLimit);
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
