
// Primary Include
#include "Engine/World.h"

namespace Fluent
{

	World::World(const std::shared_ptr<EngineStorage>& inStorage) noexcept
		: ISubModule(inStorage)
	{
	}

	bool World::Initialize()
	{
		return true;
	}

	void World::Update(f32 deltaTime)
	{
		for (const std::unique_ptr<ISystem>& system : mSystems)
		{
			system->Update(deltaTime);
		}
	}

}
