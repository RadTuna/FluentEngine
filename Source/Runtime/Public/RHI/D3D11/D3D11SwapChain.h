#pragma once

#ifdef API_GRAPHICS_D3D11

// Engine Include
#include "D3D11Definition.h"


namespace Fluent
{

	class D3D11SwapChain
	{
	public:

		D3D11SwapChain() = default;
		~D3D11SwapChain() = default;
		
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
