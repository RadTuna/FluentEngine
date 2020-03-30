#pragma once

#ifdef API_GRAPHICS_D3D11

// Engine Include
#include "D3D11Definition.h"


namespace Fluent
{

	class D3D11DepthStencilState
	{
	public:

		explicit D3D11DepthStencilState() = default;
		virtual ~D3D11DepthStencilState() = default;

		[[nodiscard]]
		ID3D11DepthStencilState* GetDepthStencilState() const { return mDepthStencilState; }
		
	protected:

		ID3D11DepthStencilState* mDepthStencilState = nullptr;
		
	};
	
}

#endif
