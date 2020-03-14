#pragma once

// Engine Include
#include "D3D11/D3DInputLayout.h"
#include "Core/Core.h"


namespace Fluent
{
	
	class InputLayout final :
#ifdef API_GRAPHICS_D3D11
		public D3DInputLayout
#endif
	{
	public:

	private:
		
	};
	
}
