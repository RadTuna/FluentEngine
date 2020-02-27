#pragma once

#include <memory>

// Engine Include
#include "Core/Core.h"
#include "RuntimeStorage.h"

namespace Fluent
{
	
	class ISubSystem
	{
	public:
		
		explicit ISubSystem(const std::shared_ptr<RuntimeStorage>& inStorage)
		{
			mStorage = inStorage;
		}
		
		virtual ~ISubSystem() = default;

		virtual bool Initialize() = 0;
		virtual void Update(float deltaTime) = 0;

	protected:

		std::shared_ptr<RuntimeStorage> mStorage;

	};

}

