#pragma once

// Engine Include
#include "Core/Core.h"
#include "Engine/IComponent.h"


namespace Fluent
{

	class TransformComponent final : public IComponent
	{
		REFLECTION_CLASS(TransformComponent, IComponent,
			)
		
	public:

		explicit TransformComponent() noexcept;
		virtual ~TransformComponent() = default;
		
	private:

		u64 Test;
		
	};
	
}
