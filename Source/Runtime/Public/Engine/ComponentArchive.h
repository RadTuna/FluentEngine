#pragma once

// External Include
#include <vector>
#include <set>

// Engine Include
#include "Core/Core.h"


namespace Fluent
{

	constexpr u32 DEFAULT_CHUNK_CAPACITY = 16384;
	constexpr u32 DEFAULT_EMPTY_INDEX_CAPACITY = 16;
	
	struct ComponentChunk
	{
	public:

		std::vector<u8> mComponents;
		std::vector<u32> mEmptyIndices;
		
	public:

		explicit ComponentChunk()
		{
			mComponents.reserve(DEFAULT_CHUNK_CAPACITY);
			mEmptyIndices.reserve(DEFAULT_EMPTY_INDEX_CAPACITY);
		}
		
		~ComponentChunk() = default;

		
		[[nodiscard]]
		bool IsEmpty() const { return mComponents.empty(); }

		[[nodiscard]]
		u32 GetRemainSize() const { return static_cast<u32>(mComponents.capacity() - mComponents.size()); }

		[[nodiscard]]
		i32 GetEmptyIndex() const { return mEmptyIndices.empty() ? INDEX_NONE : mEmptyIndices[0]; }
		
	};
	
	class ComponentArchive final
	{
	public:

		explicit ComponentArchive(const std::set<u64>& componentIDSet, u32 componentSetSize);
		~ComponentArchive();


		[[nodiscard]]
		void* GetEmptyComponentSet(bool bAllowAddChunk);

		void RemoveComponentSet(class IComponent* dest);

	private:

		void AddChunk();
		
	private:

		std::set<u64> mComponentIDSet;
		u32 mComponentSetSize;
		std::vector<ComponentChunk*> mChunks;
		
	};

}
