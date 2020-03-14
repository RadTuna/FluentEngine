#pragma once

// External Include
#include <memory>
#include <vector>

// Runtime Include
#include "Core/Core.h"

// Engine Include
#include "Core/TimeCounter.h"
#include "Core/RuntimeStorage.h"
#include "Core/ISubSystem.h"


namespace Fluent
{

	class ISubSystem;
	class RuntimeStorage;
	class TimeCounter;
	
	class Runtime final
	{
	public:

		explicit Runtime(const WindowData& windowData) noexcept;
		~Runtime() = default;

		bool Initialize();
		void Update();
		
		void SetWindowData(const WindowData& windowData);

	private:

		std::shared_ptr<RuntimeStorage> mStorage = nullptr;
		std::unique_ptr<TimeCounter> mTimeCounter = nullptr;
		
		std::vector<std::unique_ptr<ISubSystem>> mSubSystems;
		
	};
	
}
