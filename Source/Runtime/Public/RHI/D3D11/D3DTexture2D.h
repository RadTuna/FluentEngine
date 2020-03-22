#pragma once

#ifdef API_GRAPHICS_D3D11

// Engine Include
#include "D3DDefinition.h"


namespace Fluent
{

	class D3DTexture2D
	{
	public:

	protected:

		ID3D11ShaderResourceView* mShaderResourceView = nullptr;
		ID3D11RenderTargetView* mRenderTargetView = nullptr;
		
	};

}

#endif
