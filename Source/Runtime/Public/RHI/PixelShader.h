#pragma once

// Engine Include
#include "D3D11/D3DPixelShader.h"
#include "Core/Core.h"


namespace Fluent
{
	
	class PixelShader final :
#ifdef API_GRAPHICS_D3D11
		public D3DPixelShader
#endif
	{
	public:

	private:
		
	};
	
}
