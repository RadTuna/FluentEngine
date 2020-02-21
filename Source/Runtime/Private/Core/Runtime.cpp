
#include "Core/Runtime.h"
#include "Core/RuntimeStorage.h"
#include "Core/TimeCounter.h"
#include "Engine/World.h"
#include "Rendering/Renderer.h"

using namespace Fluent;

Runtime::Runtime(const WindowData& windowData)
{
	mStorage = std::make_unique<RuntimeStorage>();
	mStorage->mWindowData = windowData;
	
	mTimeCounter = std::make_unique<TimeCounter>();

	mSubSystems.reserve(8);
	mSubSystems.emplace_back(std::make_unique<World>());
	mSubSystems.emplace_back(std::make_unique<Renderer>());
}

bool Runtime::Initialize()
{
	if (mStorage == nullptr || mTimeCounter == nullptr)
	{
		return false;
	}

	for (int32 index = 0; index < mSubSystems.size(); ++index)
	{
		const bool result = mSubSystems[index]->Initialize();
		if (!result)
		{
			return false;
		}
	}

	return true;
}

void Runtime::Update()
{
	mTimeCounter->Update(mTimeCounter->GetDeltaTime());
	
	for (int32 index = 0; index < mSubSystems.size(); ++index)
	{
		const float deltaTime = mTimeCounter->GetDeltaTime();
		mSubSystems[index]->Update(deltaTime);
	}
}

void Runtime::SetWindowData(const WindowData& windowData)
{
	mStorage->mWindowData = windowData;
}
