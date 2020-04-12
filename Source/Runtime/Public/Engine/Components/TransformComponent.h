#pragma once

// Engine Include
#include "Core/Core.h"
#include "Engine/IComponent.h"


namespace Fluent
{

	class TransformComponent final : public IComponent
	{
	public:

		REGISTER_COMPONENT()

		explicit TransformComponent() = default;
		virtual ~TransformComponent() = default;
		
	private:
		
	};
	
}
