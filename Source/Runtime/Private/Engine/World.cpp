
// Primary Include
#include "Engine/World.h"

// Engine Include

namespace Fluent
{

	World::World(const std::shared_ptr<SystemStorage>& inStorage) noexcept
		: ISubModule(inStorage)
	{
	}

	bool World::Initialize()
	{

		return true;
	}

	void World::Update(f32 deltaTime)
	{

	}

}
