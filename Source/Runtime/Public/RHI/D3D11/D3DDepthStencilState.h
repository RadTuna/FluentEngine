#pragma once

#include "D3DDefinition.h"

#ifdef API_GRAPHICS_D3D11

namespace Fluent
{

	class D3DDepthStencilState
	{
	public:

		explicit D3DDepthStencilState() = default;
		virtual ~D3DDepthStencilState() = default;

		[[nodiscard]]
		ID3D11DepthStencilState* GetDepthStencilState() const { return mDepthStencilState; }
		
	protected:

		ID3D11DepthStencilState* mDepthStencilState = nullptr;
		
	};
	
}

#endif
