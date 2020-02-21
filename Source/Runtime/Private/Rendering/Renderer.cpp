
#include "Rendering/Renderer.h"

using namespace Fluent;

Renderer::Renderer(RuntimeStorage* inStorage) noexcept
    : Super(inStorage)
{
}

Renderer::~Renderer()
{
}

bool Renderer::Initialize()
{
    HRESULT handleResult = S_OK;

    RECT winRect;
    GetClientRect(mWindowHandle, &winRect);
    const uint32 width = winRect.right - winRect.left;
    const uint32 height = winRect.bottom - winRect.top;
	
    uint32 createDeviceFlags = 0;

#ifdef _DEBUG

    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	
#endif

	
    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
    UINT numFeatureLevels = sizeof(featureLevels) / sizeof(D3D_FEATURE_LEVEL);

    handleResult = D3D11CreateDevice(
        nullptr, 
        D3D_DRIVER_TYPE_HARDWARE, 
        nullptr, 
        createDeviceFlags,
        featureLevels, 
        numFeatureLevels, 
        D3D11_SDK_VERSION, 
        &mDevice, 
        nullptr, 
        &mDeviceContext);
	if (FAILED(handleResult))
	{
        return false;
	}

    IDXGIFactory* dxgiFactory = nullptr;
    IDXGIDevice* dxgiDevice = nullptr;
    handleResult = mDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
	if (SUCCEEDED(handleResult))
	{
        IDXGIAdapter* dxgiAdapter = nullptr;
        handleResult = dxgiDevice->GetAdapter(&dxgiAdapter);
		if (SUCCEEDED(handleResult))
		{
            dxgiAdapter->QueryInterface(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&dxgiFactory));
            dxgiAdapter->Release();
		}

        dxgiDevice->Release();
	}
    if (FAILED(handleResult))
    {
        return false;
    }

    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    swapChainDesc.BufferCount = 1;
    swapChainDesc.BufferDesc.Width = width;
    swapChainDesc.BufferDesc.Height = height;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.OutputWindow = mWindowHandle;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.Windowed = true;

    handleResult = dxgiFactory->CreateSwapChain(mDevice, &swapChainDesc, &mSwapChain);
    dxgiFactory->Release();
	if (FAILED(handleResult))
	{
        return false;
	}

    ID3D11Texture2D* backBuffer = nullptr;
    handleResult = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer));
	if (FAILED(handleResult))
	{
        return false;
	}

    handleResult = mDevice->CreateRenderTargetView(backBuffer, nullptr, &mRenderTargetView);
    backBuffer->Release();
	if (FAILED(handleResult))
	{
        return false;
	}

    mDeviceContext->OMSetRenderTargets(1, &mRenderTargetView, nullptr);

    CreateConstantBuffers();
    CreateShaders();
    CreateDepthStencilStates();
    CreateRasterizerStates();
    CreateRenderTargets();

    return true;
}

void Renderer::Update(float deltaTime)
{
}

void Renderer::CreateConstantBuffers()
{
}

void Renderer::CreateShaders()
{
}

void Renderer::CreateDepthStencilStates()
{
}

void Renderer::CreateRasterizerStates()
{
}

void Renderer::CreateRenderTargets()
{
}
