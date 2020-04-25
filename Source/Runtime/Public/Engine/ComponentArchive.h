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

		std::vector<u8> Components;
		std::vector<u32> EmptyIndices;
		
	public:

		explicit ComponentChunk()
		{
			Components.reserve(DEFAULT_CHUNK_CAPACITY);
			EmptyIndices.reserve(DEFAULT_EMPTY_INDEX_CAPACITY);
		}
		
		~ComponentChunk() = default;

		
		[[nodiscard]]
		bool IsEmpty() const { return Components.empty(); }

		[[nodiscard]]
		u32 GetRemainSize() const { return static_cast<u32>(Components.capacity() - Components.size()); }

		[[nodiscard]]
		i32 GetEmptyIndex() const { return EmptyIndices.empty() ? INDEX_NONE : EmptyIndices[0]; }
		
	};
	
	class ComponentArchive final
	{
	public:

		explicit ComponentArchive(const std::set<u64>& componentIDSet, u32 componentSetSize);
		~ComponentArchive();


		[[nodiscard]]
		void* GetEmptyComponentSet();

		void RemoveComponentSet(class IComponent* dest);

		[[nodiscard]]
		bool IsEqualIDSet(const std::set<u64>& componentIDSet) const;

	private:

		void AddChunk();
		
	private:

		std::set<u64> mComponentIDSet;
		u32 mComponentSetSize;
		std::vector<ComponentChunk*> mChunks;
		
	};

}
