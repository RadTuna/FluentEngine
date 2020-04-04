#pragma once

// Engine Include
#include "RHI/Texture.h"
#include "D3D11/D3D11Texture3D.h"


namespace Fluent
{

	class Texture3D final : public Texture,
#ifdef API_GRAPHICS_D3D11
		public D3D11Texture3D
#endif
	{
	public:

	private:
		
	};
	
}
