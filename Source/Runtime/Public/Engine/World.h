#pragma once

// Engine Include
#include "Core/Core.h"
#include "Core/ISubSystem.h"


namespace Fluent
{

	class World : public ISubSystem
	{
	public:

		using Super = ISubSystem;

		explicit World(class RuntimeStorage* inStorage) noexcept;
		virtual ~World() = default;

		bool Initialize() override;
		void Update(float deltaTime) override;

	private:
	};

}
