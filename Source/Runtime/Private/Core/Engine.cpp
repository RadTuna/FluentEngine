
// Primary Include
#include "Core/Engine.h"

// Engine Include
#include "Engine/World.h"
#include "Rendering/Renderer.h"


namespace Fluent
{

	Engine::Engine(const WindowData& windowData) noexcept
	{
		mStorage = std::make_shared<SystemStorage>();
		mStorage->SetWindowData(windowData);

		mTimeCounter = std::make_unique<TimeCounter>(mStorage);

		mSubModules.reserve(8);
		mSubModules.emplace_back(std::make_unique<World>(mStorage));
		mSubModules.emplace_back(std::make_unique<Renderer>(mStorage));
	}

	bool Engine::Initialize()
	{	
		if (mStorage == nullptr || mTimeCounter == nullptr)
		{
			return false;
		}

		mTimeCounter->Initialize();

		for (u32 index = 0; index < mSubModules.size(); ++index)
		{
			const bool result = mSubModules[index]->Initialize();
			if (!result)
			{
				return false;
			}
		}

		return true;
	}

	void Engine::Update()
	{
		mTimeCounter->Update(mTimeCounter->GetDeltaTime());
		const f32 deltaTime = mTimeCounter->GetDeltaTime();
		
		for (const std::unique_ptr<ISubModule>& subSystem : mSubModules)
		{
			subSystem->Update(deltaTime);
		}
	}

	void Engine::SetWindowData(const WindowData& windowData)
	{
		mStorage->SetWindowData(windowData);
	}

    void Engine::SetWindowMessage(const WindowMsg& windowMsg)
    {
		mStorage->SetWindowMessage(windowMsg);
    }
}
