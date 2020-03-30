#pragma once

#ifdef API_GRAPHICS_D3D11

// Engine Include
#include "D3D11Definition.h"


namespace Fluent
{

	class D3D11RasterizerState
	{
	public:

		explicit D3D11RasterizerState() = default;
		virtual ~D3D11RasterizerState() = default;

		[[nodiscard]]
		ID3D11RasterizerState* GetRasterizerState() const { return mRasterizerState; }

		[[nodiscard]]
		D3D11_CULL_MODE ToD3DCullMode(ERenderCullMode cullMode);
		[[nodiscard]]
		D3D11_FILL_MODE ToD3DFillMode(ERenderFillMode fillMode);

	protected:

		ID3D11RasterizerState* mRasterizerState = nullptr;
		
	};
	
}

#endif
