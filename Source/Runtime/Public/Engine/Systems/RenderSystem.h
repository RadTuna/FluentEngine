#pragma once

// Engine Include
#include "Core/Core.h"
#include "Engine/ISystem.h"


namespace Fluent
{

	class RenderSystem final : public ISystem
	{
		REFLECTION_CLASS(RenderSystem, ISystem)
		
	public:

		explicit RenderSystem() = default;
		virtual ~RenderSystem() = default;
		
	private:
		
	};
	
}
