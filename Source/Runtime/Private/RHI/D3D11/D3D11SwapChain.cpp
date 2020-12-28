
#ifdef API_GRAPHICS_D3D11

// Primary Include
#include "RHI/SwapChain.h"

// Engine Include
#include "Core/SystemStorage.h"
#include "RHI/Device.h"

namespace Fluent
{

	SwapChain::SwapChain(const std::shared_ptr<Device>& device, const WindowData& winData) noexcept
	{
		Assert(device && device->IsInitialized());
		
		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		swapChainDesc.BufferCount = 1;
		swapChainDesc.BufferDesc.Width = static_cast<u32>(winData.ScreenWidth);
		swapChainDesc.BufferDesc.Height = static_cast<u32>(winData.ScreenHeight);
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.OutputWindow = static_cast<HWND>(winData.Handle);
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.Windowed = true;

		IDXGIFactory* dxgiFactory = nullptr;
		HRESULT result = device->GetAdapter()->GetParent(IID_PPV_ARGS(&dxgiFactory));
		if (FAILED(result))
		{
			mbIsInitialized = false;
			return;
		}

		result = dxgiFactory->CreateSwapChain(device->GetDevice(), &swapChainDesc, &mSwapChain);
		dxgiFactory->Release();
		dxgiFactory = nullptr;
		if (FAILED(result))
		{
			mbIsInitialized = false;
			return;
		}

		ID3D11Texture2D* backBuffer = nullptr;
		result = mSwapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
		if (FAILED(result))
		{
			mbIsInitialized = false;
			return;
		}

		result = device->GetDevice()->CreateRenderTargetView(backBuffer, nullptr, &mRenderTargetView);
		backBuffer->Release();
		if (FAILED(result))
		{
			mbIsInitialized = false;
			return;
		}

		mbIsInitialized = true;
	}

	SwapChain::~SwapChain() noexcept
	{
		D3D11Release(mRenderTargetView);
		D3D11Release(mSwapChain);
	}

	bool SwapChain::Present() const
	{
		HRESULT handleResult = S_OK;
		handleResult = mSwapChain->Present(mSyncInterval, mFlags);
		if (FAILED(handleResult))
		{
			return false;
		}

		return true;
	}
}

#endif
