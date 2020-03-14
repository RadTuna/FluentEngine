#pragma once

// Engine Include
#include "D3D11/D3DVertex.h"
#include "Core/Core.h"


namespace Fluent
{
	
	class Vertex final :
#ifdef API_GRAPHICS_D3D11
		public D3DVertex
#endif
	{
	public:

	private:
		
	};
	
}
