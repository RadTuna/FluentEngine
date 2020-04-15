#pragma once

// Engine Include
#include "Core/Core.h"
#include "Engine/ISystem.h"


namespace Fluent
{

	class MovementSystem final : public ISystem
	{
		REFLECTION_CLASS(MovementSystem, ISystem)
		
	public:

		explicit MovementSystem() = default;
		virtual ~MovementSystem() = default;

	private:

	};

}
