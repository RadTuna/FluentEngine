#pragma once

// External Include
#include <memory>
#include <vector>

// Engine Include
#include "Core/Core.h"
#include "Core/ISubModule.h"
#include "Entity.h"
#include "ComponentArchive.h"
#include "ISystem.h"


namespace Fluent
{
	
	class World final : public ISubModule
	{
	public:

		explicit World(const std::shared_ptr<EngineStorage>& inStorage) noexcept;
		virtual ~World() = default;

		bool Initialize() override;
		void Update(f32 deltaTime) override;


		// Component function;
		void AddComponentPack(class ComponentPack* componentPack, bool bAllowAddArchive = true);

	private:

		void AddComponentArchive(const class ComponentPack& componentPack);

	private:

		std::vector<Entity> mEntities;
		std::vector<ComponentArchive> mComponents;
		std::vector<std::unique_ptr<ISystem>> mSystems;
		
	};

}
