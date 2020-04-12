#pragma once

#include <memory>

// Engine Include
#include "Core/Core.h"

namespace Fluent
{
	class EngineStorage;
	
	class ISubModule
	{
	public:
		
		explicit ISubModule(const std::shared_ptr<EngineStorage>& inStorage)
		{
			mStorage = inStorage;
		}
		
		virtual ~ISubModule() = default;

		virtual bool Initialize() = 0;
		virtual void Update(float deltaTime) = 0;

	protected:

		std::shared_ptr<EngineStorage> mStorage;

	};

}

