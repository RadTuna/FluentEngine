
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

	void* ComponentArchive::GetEmptyComponentSet(bool bAllowAddChunk)
	{
		for (ComponentChunk* chunk : mChunks)
		{
			if (chunk->GetEmptyIndex() != INDEX_NONE)
			{
				// Pointer calculation
				return chunk->mComponents.data() + chunk->GetEmptyIndex();
			}

			if (mComponentSetSize <= chunk->GetRemainSize())
			{
				// Pointer calculation
				return chunk->mComponents.data() + chunk->mComponents.size();
			}
		}

		return nullptr;
	}

	void ComponentArchive::RemoveComponentSet(IComponent* dest)
	{
		const u8* const purePtr = reinterpret_cast<u8*>(dest);

		bool bIsFindChunk = false;
		for (ComponentChunk* chunk : mChunks)
		{
			// Pointer calculation
			const u8* const chunkBasePtr = chunk->mComponents.data();
			const u8* const chunkTopPtr = chunk->mComponents.data() + DEFAULT_CHUNK_CAPACITY - mComponentSetSize;
			if (chunkBasePtr >= purePtr && chunkTopPtr < purePtr)
			{
				// Pointer calculation
				const i64 ptrDiff = purePtr - chunkBasePtr;
				chunk->mEmptyIndices.emplace_back(static_cast<u32>(ptrDiff));

				bIsFindChunk = true;
				break;
			}
		}

		if (bIsFindChunk)
		{
			MemSet(dest, 0, mComponentSetSize);
		}
	}

	void ComponentArchive::AddChunk()
	{
		ComponentChunk* const newComponentChunk = New<ComponentChunk>();
		mChunks.emplace_back(newComponentChunk);
	}
}
