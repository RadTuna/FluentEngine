
#include "Engine/World.h"

using namespace Fluent;

World::World(RuntimeStorage* inStorage) noexcept
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
