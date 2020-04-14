
// Primary Include
#include "Engine/World.h"

// Engine Include
#include "Engine/ComponentPack.h"
#include "Engine/Components/RenderComponent.h"
#include "Engine/Components/TransformComponent.h"

namespace Fluent
{

	World::World(const std::shared_ptr<EngineStorage>& inStorage) noexcept
		: ISubModule(inStorage)
	{
	}

	bool World::Initialize()
	{
		// temp code
		ComponentPack testPack;
		RenderComponent* RenderComp = nullptr;
		TransformComponent* TransformComp = nullptr;
		testPack.AppendComponent(&RenderComp);
		testPack.AppendComponent(&TransformComp);

		AddComponentPack(&testPack);
		// temp code
		
		return true;
	}

	void World::Update(f32 deltaTime)
	{
		for (const std::unique_ptr<ISystem>& system : mSystems)
		{
			system->Update(deltaTime);
		}
	}

	void World::AddComponentPack(ComponentPack* componentPack, bool bAllowAddArchive)
	{
		Assert(componentPack->ComponentIDSet.size() == componentPack->ComponentSize.size());
		
		for (ComponentArchive& componentArchive : mComponents)
		{
			if (!componentArchive.IsEqualIDSet(componentPack->ComponentIDSet))
			{
				continue;
			}

			u8* basePtr = static_cast<u8*>(componentArchive.GetEmptyComponentSet());
			u64 topIndex = 0;
			for (u32 index = 0; index < componentPack->ComponentIDSet.size(); ++index)
			{	
				*(componentPack->ComponentPtr[index]) = reinterpret_cast<void*>(basePtr + topIndex);
				topIndex += componentPack->ComponentSize[index];
			}

			componentPack->MoveInitData(basePtr, topIndex);
		}

		if (bAllowAddArchive)
		{
			AddComponentArchive(*componentPack);
			AddComponentPack(componentPack, false);
		}
	}

	void World::AddComponentArchive(const ComponentPack& componentPack)
	{
		u32 totalSize = 0;
		for (const u32 separateSize : componentPack.ComponentSize)
		{
			totalSize += separateSize;
		}
		
		mComponents.emplace_back(componentPack.ComponentIDSet, totalSize);
	}
	
}
