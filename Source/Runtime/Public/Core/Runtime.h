#pragma once

// External Include
#include <memory>
#include <vector>

// Runtime Include
#include "Core/Core.h"
#include "Core/TypeDefinition.h"

// Engine Include
#include "Core/ISubSystem.h"
#include "Core/RuntimeStorage.h"
#include "Core/TimeCounter.h"


namespace Fluent
{
	
	class Runtime
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
