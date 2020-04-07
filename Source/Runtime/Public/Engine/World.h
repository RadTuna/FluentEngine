#pragma once

// External Include
#include <memory>
#include <vector>

// Engine Include
#include "Core/Core.h"
#include "Core/ISubSystem.h"

namespace Fluent
{
	
	class World final : public ISubSystem
	{
	public:

		explicit World(const std::shared_ptr<RuntimeStorage>& inStorage) noexcept;
		virtual ~World() = default;

		bool Initialize() override;
		void Update(f32 deltaTime) override;

	private:

		std::vector<class Entity*> mEntities;
		std::vector<class IComponent*> mComponents;
		std::vector<class ISystem*> mSystems;
		
	};

}
