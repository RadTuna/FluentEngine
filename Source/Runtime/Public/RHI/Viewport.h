#pragma once

// Engine Include
#include "D3D11/D3DViewport.h"
#include "Core/Core.h"


namespace Fluent
{
	
	class Viewport final :
#ifdef API_GRAPHICS_D3D11
		public D3DViewport
#endif
	{
	public:

	private:
		
	};
	
}
