#pragma once

// Engine Include
#include "D3D11/D3DCommandList.h"
#include "Core/Core.h"


namespace Fluent
{
	
	class CommandList :
#ifdef API_GRAPHICS_D3D11
		public D3DCommandList
#endif
	{
	public:

	private:
		
	};

}
