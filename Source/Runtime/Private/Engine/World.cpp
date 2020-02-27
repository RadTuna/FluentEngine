
#include "Engine/World.h"

using namespace Fluent;

World::World(const std::shared_ptr<RuntimeStorage>& inStorage) noexcept
	: Super(inStorage)
{
}

bool World::Initialize()
{
	return false;
}

void World::Update(float deltaTime)
{
	return;
}
