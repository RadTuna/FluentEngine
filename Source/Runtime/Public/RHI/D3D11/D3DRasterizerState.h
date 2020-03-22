#pragma once

#include "D3DDefinition.h"

#ifdef API_GRAPHICS_D3D11

namespace Fluent
{

	class D3DRasterizerState
	{
	public:

		explicit D3DRasterizerState() = default;
		virtual ~D3DRasterizerState() = default;

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
