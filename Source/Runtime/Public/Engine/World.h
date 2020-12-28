#pragma once

// External Include
#include <memory>
#include <vector>

// Engine Include
#include "Core/Core.h"
#include "Core/ISubModule.h"


namespace Fluent
{
	
	class World final : public ISubModule
	{
	public:

		explicit World(const std::shared_ptr<SystemStorage>& inStorage) noexcept;
		virtual ~World() = default;

		bool Initialize() override;
		void Update(f32 deltaTime) override;
		
	};

}
