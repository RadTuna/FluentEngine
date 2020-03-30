#pragma once

// Engine Include
#include "D3D11/D3D11CommandList.h"
#include "Core/Core.h"


namespace Fluent
{
	
	class CommandList :
#ifdef API_GRAPHICS_D3D11
		public D3D11CommandList
#endif
	{
	public:

	private:
		
	};

}
