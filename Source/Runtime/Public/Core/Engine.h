#pragma once

// External Include
#include <memory>
#include <vector>

// Engine Include
#include "Core/Core.h"

// Engine Include
#include "Core/TimeCounter.h"
#include "Core/EngineStorage.h"
#include "Core/ISubModule.h"


namespace Fluent
{

	class ISubModule;
	class EngineStorage;
	class TimeCounter;
	
	class Engine final
	{
	public:

		explicit Engine(const WindowData& windowData) noexcept;
		~Engine() = default;

		bool Initialize();
		void Update();
		
		void SetWindowData(const WindowData& windowData);

	private:

		std::shared_ptr<EngineStorage> mStorage = nullptr;
		std::unique_ptr<TimeCounter> mTimeCounter = nullptr;
		
		std::vector<std::unique_ptr<ISubModule>> mSubModules;
		
	};
	
}
