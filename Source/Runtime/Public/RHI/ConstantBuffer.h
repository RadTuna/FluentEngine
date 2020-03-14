#pragma once

// Engine Include
#include "D3D11/D3DConstantBuffer.h"
#include "Core/Core.h"


namespace Fluent
{
	
	class ConstantBuffer :
#ifdef API_GRAPHICS_D3D11
		public D3DConstantBuffer
#endif
	{
	public:

	private:

	};
	
}
