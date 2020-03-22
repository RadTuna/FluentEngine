#pragma once

#ifdef API_GRAPHICS_D3D11

// Engine Include
#include "D3DDefinition.h"


namespace Fluent
{

	class D3DSwapChain
	{
	public:

		D3DSwapChain() = default;
		~D3DSwapChain() = default;
		
		[[nodiscard]]
		IDXGISwapChain* GetSwapChain() const { return mSwapChain; }

		[[nodiscard]]
		ID3D11RenderTargetView* GetRenderTargetView() const { return mRenderTargetView; }
		
	protected:

		IDXGISwapChain* mSwapChain = nullptr;
		ID3D11RenderTargetView* mRenderTargetView = nullptr;
		
	};

}

#endif
