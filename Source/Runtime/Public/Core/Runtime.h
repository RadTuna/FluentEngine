#pragma once

// External Include
#include <memory>
#include <vector>

// Runtime Include
#include "Core/Core.h"
#include "Core/TypeDefinition.h"


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

		std::unique_ptr<class RuntimeStorage> mStorage = nullptr;
		std::unique_ptr<class TimeCounter> mTimeCounter = nullptr;
		
		std::vector<std::unique_ptr<class ISubSystem>> mSubSystems;
		
	};
	
}
