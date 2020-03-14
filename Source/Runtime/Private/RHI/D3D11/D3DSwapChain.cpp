
#ifdef API_GRAPHICS_D3D11

#include "RHI/SwapChain.h"
#include "Core/RuntimeStorage.h"
#include "RHI/Device.h"

namespace Fluent
{

	SwapChain::SwapChain(const std::shared_ptr<Device>& device, const WindowData& winData) noexcept
	{
		HRESULT handleResult = S_OK;

		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		swapChainDesc.BufferCount = 1;
		swapChainDesc.BufferDesc.Width = static_cast<uint32>(winData.ScreenWidth);
		swapChainDesc.BufferDesc.Height = static_cast<uint32>(winData.ScreenHeight);
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.OutputWindow = winData.Handle;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.Windowed = true;

		IDXGIFactory* dxgiFactory = nullptr;
		handleResult = device->GetAdapter()->GetParent(IID_PPV_ARGS(&dxgiFactory));
		if (FAILED(handleResult))
		{
			mbIsInitialized = false;
			return;
		}

		handleResult = dxgiFactory->CreateSwapChain(device->GetDevice(), &swapChainDesc, &mSwapChain);
		dxgiFactory->Release();
		dxgiFactory = nullptr;
		if (FAILED(handleResult))
		{
			mbIsInitialized = false;
			return;
		}

		ID3D11Texture2D* backBuffer = nullptr;
		handleResult = mSwapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
		if (FAILED(handleResult))
		{
			mbIsInitialized = false;
			return;
		}

		handleResult = device->GetDevice()->CreateRenderTargetView(backBuffer, nullptr, &mRenderTargetView);
		backBuffer->Release();
		if (FAILED(handleResult))
		{
			mbIsInitialized = false;
			return;
		}

		mbIsInitialized = true;
	}

	SwapChain::~SwapChain() noexcept
	{
		
	}

	void SwapChain::TempSetRenderTarget(const std::shared_ptr<Device>& device) const
	{
		device->GetDeviceContext()->OMSetRenderTargets(1, &mRenderTargetView, nullptr);
	}

	void SwapChain::TempSetColorRed(const std::shared_ptr<Device>& device) const
	{
		// temp
		float color[4];
		color[0] = 1.0f;
		color[1] = 0.0f;
		color[2] = 0.0f;
		color[3] = 1.0f;
		
		device->GetDeviceContext()->ClearRenderTargetView(mRenderTargetView, color);
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
