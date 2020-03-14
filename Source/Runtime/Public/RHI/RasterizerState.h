#pragma once

// Engine Include
#include "D3D11/D3DRasterizerState.h"
#include "Core/Core.h"


namespace Fluent
{
	
	class RasterizerState final :
#ifdef API_GRAPHICS_D3D11
		public D3DRasterizerState
#endif
	{
	public:

	private:
		
	};
	
}
