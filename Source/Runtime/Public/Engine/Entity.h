#pragma once

// External Include
#include <memory>
#include <vector>

// Engine Include
#include "Core/Core.h"


namespace Fluent
{

	class Entity final
	{
	public:

		explicit Entity(u32 id) noexcept;
		~Entity() noexcept;
		
	private:

		u32 mID;
		
		std::vector<class IComponent*> mComponents;
		
	};
	
}
