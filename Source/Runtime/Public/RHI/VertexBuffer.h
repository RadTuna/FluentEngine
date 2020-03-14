#pragma once

// Engine Include
#include "D3D11/D3DVertexBuffer.h"
#include "Core/Core.h"


namespace Fluent
{
	
	class VertexBuffer final :
#ifdef API_GRAPHICS_D3D11
		public D3DVertexBuffer
#endif
	{
	public:

	private:
		
	};
	
}
