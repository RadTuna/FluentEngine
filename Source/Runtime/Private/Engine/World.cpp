
#include "Engine/World.h"


namespace Fluent
{

	World::World(const std::shared_ptr<RuntimeStorage>& inStorage) noexcept
		: ISubSystem(inStorage)
	{
	}

	bool World::Initialize()
	{
		return true;
	}

	void World::Update(float deltaTime)
	{
		return;
	}

}
