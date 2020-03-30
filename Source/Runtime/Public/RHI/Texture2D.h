#pragma once

#include "Texture.h"
#include "D3D11/D3D11Texture2D.h"


namespace Fluent
{

	class Texture2D : public Texture,
#ifdef API_GRAPHICS_D3D11
		public D3D11Texture2D
#endif
	{
	public:

	private:
		
	};
	
}
