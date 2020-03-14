#pragma once

// Engine Include
#include "D3D11/D3DIndexBuffer.h"
#include "Core/Core.h"


namespace Fluent
{
	
	class IndexBuffer final :
#ifdef API_GRAPHICS_D3D11
		public D3DIndexBuffer
#endif
	{
	public:

	private:
		
	};
	
}
