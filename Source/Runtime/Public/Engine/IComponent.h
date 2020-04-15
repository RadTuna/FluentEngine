#pragma once

// External Include
#include <map>

// Engine Include
#include "Core/Core.h"


namespace Fluent
{
	
	class IComponent
	{
		REFLECTION_CLASS_NO_SUPER(IComponent)
		
	public:

		explicit IComponent() = default;
		virtual ~IComponent() = default;

	};
	
}
