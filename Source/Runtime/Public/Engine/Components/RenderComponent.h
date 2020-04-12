#pragma once

// Engine Include
#include "Core/Core.h"
#include "Engine/IComponent.h"


namespace Fluent
{

	class RenderComponent final : public IComponent
	{
	public:

		REGISTER_COMPONENT()

		explicit RenderComponent() = default;
		virtual ~RenderComponent() = default;

	private:

	};

}

