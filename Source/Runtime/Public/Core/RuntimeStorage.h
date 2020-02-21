#pragma once

// Engine Include
#include "Core/Core.h"
#include "TypeDefinition.h"


namespace Fluent
{

	class RuntimeStorage
	{
	public:

		explicit RuntimeStorage() = default;
		~RuntimeStorage() = default;

	public:

		WindowData mWindowData;
	};

}
