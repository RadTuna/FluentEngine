#pragma once

// Engine Include
#include "Core/Core.h"
#include "Engine/IComponent.h"

// test
#include "Math/Vector4.h"

namespace Fluent
{

	class TransformComponent final : public IComponent
	{
		CLASS_BODY(TransformComponent, IComponent);
		
	public:

		explicit TransformComponent() noexcept;
		virtual ~TransformComponent() = default;


		// test var
		Vector4 mLocation;
		
	private:
		
	};
	
}
