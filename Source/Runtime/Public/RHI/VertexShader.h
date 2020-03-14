#pragma once

// Engine Include
#include "D3D11/D3DVertexShader.h"
#include "Core/Core.h"


namespace Fluent
{
	
	class VertexShader final :
#ifdef API_GRAPHICS_D3D11
		public D3DVertexShader
#endif
	{
	public:

	private:
		
	};
	
}
