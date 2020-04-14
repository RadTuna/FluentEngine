#pragma once

// Engine Include
#include "Core/Core.h"
#include "Engine/IComponent.h"


namespace Fluent
{

	class RenderComponent final : public IComponent
	{
	public:

		REGISTER_COMPONENT(RenderComponent)

		explicit RenderComponent() noexcept;
		virtual ~RenderComponent() = default;

		
		// test var
		i32 TestNumber = 0;
		
	private:

	};

}

