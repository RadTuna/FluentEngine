#pragma once

// External Include
#include <memory>
#include <vector>

// Engine Include
#include "Core/Core.h"
#include "Engine/ComponentPack.h"


namespace Fluent
{

	class Entity final
	{
	public:

		explicit Entity(u32 id) noexcept;
		~Entity() noexcept;
		
	private:

		u64 mID;
		
		std::shared_ptr<ComponentPack> mComponents;
		
	};
	
}
