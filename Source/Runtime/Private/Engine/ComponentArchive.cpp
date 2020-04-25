
// Primary Include
#include "Engine/ComponentArchive.h"

// Engine Include
#include "Engine/IComponent.h"


namespace Fluent
{
	ComponentArchive::ComponentArchive(const std::set<u64>& componentIDSet, u32 componentSetSize)
	{
		mComponentIDSet = componentIDSet;
		mComponentSetSize = componentSetSize;

		mChunks.reserve(16);
	}

	ComponentArchive::~ComponentArchive()
	{
		for (ComponentChunk* chunk : mChunks)
		{
			if (chunk)
			{
				Delete(chunk);
			}
		}
	}

	void* ComponentArchive::GetEmptyComponentSet()
	{
		for (ComponentChunk* chunk : mChunks)
		{
			if (chunk->GetEmptyIndex() != INDEX_NONE)
			{
				// Pointer calculation
				return chunk->Components.data() + chunk->GetEmptyIndex();
			}

			if (mComponentSetSize <= chunk->GetRemainSize())
			{
				// Pointer calculation
				return chunk->Components.data() + chunk->Components.size();
			}
		}

		AddChunk();
		return GetEmptyComponentSet();
	}

	void ComponentArchive::RemoveComponentSet(IComponent* dest)
	{
		const u8* const purePtr = reinterpret_cast<u8*>(dest);

		bool bIsFindChunk = false;
		for (ComponentChunk* chunk : mChunks)
		{
			// Pointer calculation
			const u8* const chunkBasePtr = chunk->Components.data();
			const u8* const chunkTopPtr = chunk->Components.data() + DEFAULT_CHUNK_CAPACITY - mComponentSetSize;
			if (chunkBasePtr >= purePtr && chunkTopPtr < purePtr)
			{
				// Pointer calculation
				const i64 ptrDiff = purePtr - chunkBasePtr;
				chunk->EmptyIndices.emplace_back(static_cast<u32>(ptrDiff));

				bIsFindChunk = true;
				break;
			}
		}

		if (bIsFindChunk)
		{
			MemSet(dest, 0, mComponentSetSize);
		}
	}

	bool ComponentArchive::IsEqualIDSet(const std::set<u64>& componentIDSet) const
	{
		return mComponentIDSet == componentIDSet;
	}

	void ComponentArchive::AddChunk()
	{
		ComponentChunk* const newComponentChunk = New<ComponentChunk>();
		mChunks.emplace_back(newComponentChunk);
	}
}
