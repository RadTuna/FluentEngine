#pragma once

// Engine Include
#include "Core/Core.h"


namespace Fluent
{

	class ISystem
	{
	public:

		explicit ISystem() = default;
		virtual ~ISystem() = default;


		virtual void Update(f32 deltaTime) = 0;
		
	private:
	};
	
}
