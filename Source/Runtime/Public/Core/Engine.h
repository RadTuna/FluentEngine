#pragma once

// External Include
#include <memory>
#include <vector>

// Engine Include
#include "Core/Core.h"

// Engine Include
#include "Core/TimeCounter.h"
#include "Core/SystemStorage.h"
#include "Core/ISubModule.h"


namespace Fluent
{

	class ISubModule;
	class SystemStorage;
	class TimeCounter;
	
	class Engine final
	{
	public:

		explicit Engine(const WindowData& windowData) noexcept;
		~Engine() = default;

		bool Initialize();
		void Update();
		
		void SetWindowData(const WindowData& windowData);
		void SetWindowMessage(const WindowMsg& windowMsg);

	private:

		std::shared_ptr<SystemStorage> mStorage = nullptr;
		std::unique_ptr<TimeCounter> mTimeCounter = nullptr;
		
		std::vector<std::unique_ptr<ISubModule>> mSubModules;
		
	};
	
}
