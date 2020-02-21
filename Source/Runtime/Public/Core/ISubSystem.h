#pragma once

// Engine Include
#include "Core/Core.h"

namespace Fluent
{
	
	class ISubSystem
	{
	public:

		explicit ISubSystem(class RuntimeStorage* inStorage) : mStorage(inStorage) {}
		virtual ~ISubSystem() = default;

		virtual bool Initialize() = 0;
		virtual void Update(float deltaTime) = 0;

	protected:

		class RuntimeStorage* mStorage;

	};

}

