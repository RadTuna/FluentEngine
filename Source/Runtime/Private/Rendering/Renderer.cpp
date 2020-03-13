
#include "Rendering/Renderer.h"

using namespace Fluent;

Renderer::Renderer(const std::shared_ptr<RuntimeStorage>& inStorage) noexcept
	: Super(inStorage)
{
	mAdapter = nullptr;
	mDevice = nullptr;
	mDeviceContext = nullptr;
	mSwapChain = nullptr;
	mRenderTargetView = nullptr;
}

Renderer::~Renderer()
{
	if (mRenderTargetView != nullptr)
	{
		mRenderTargetView->Release();
		mRenderTargetView = nullptr;
	}
	
	if (mSwapChain != nullptr)
	{
		mSwapChain->Release();
		mSwapChain = nullptr;
	}

	if (mDeviceContext != nullptr)
	{
		mDeviceContext->Release();
		mDeviceContext = nullptr;
	}

	if (mDevice != nullptr)
	{
		mAdapter->Release();
		mAdapter = nullptr;
	}

	if (mAdapter != nullptr)
	{
		mAdapter->Release();
		mAdapter = nullptr;
	}
}

bool Renderer::Initialize()
{
	bool initResult = false;
	initResult = CreateDevice();
	if (!initResult)
	{
		return false;
	}
	
	initResult = CreateSwapChain();
	if (!initResult)
	{
		return false;
	}

	
	// temp
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
	// temp
	float color[4];
	color[0] = 1.0f;
	color[1] = 0.0f;
	color[2] = 0.0f;
	color[3] = 1.0f;
	mDeviceContext->ClearRenderTargetView(mRenderTargetView, color);
	
	mSwapChain->Present(0, 0);
}

void Renderer::DetectAdapter()
{
	// Create dxgi factory
	IDXGIFactory1* dxgiFactory = nullptr;
	HRESULT result = CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory));
	if (FAILED(result))
	{
		return;
	}

	
	// Get primary graphic card (num 0)
	IDXGIAdapter* adapter = nullptr;
	result = dxgiFactory->EnumAdapters(0, &adapter);
	dxgiFactory->Release();
	dxgiFactory = nullptr;
	if (FAILED(result))
	{
		return;
	}
	mAdapter = adapter;
	
	// Write device information
	DXGI_ADAPTER_DESC adapterDesc = {};
	result = adapter->GetDesc(&adapterDesc);
	if (FAILED(result))
	{
		return;
	}

	char name[128];
	const char defChar = ' ';
	WideCharToMultiByte(CP_ACP, 0, adapterDesc.Description, -1, name, 128, &defChar, nullptr);
	mDeviceData.DeviceName = name;
	mDeviceData.Memory = static_cast<uint32>(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

	
	// Get primary monitor (connected graphic card, num 0)
	IDXGIOutput* dxgiOutput = nullptr;
	result = adapter->EnumOutputs(0, &dxgiOutput);
	if (FAILED(result))
	{
		return;
	}

	uint32 displayCount = 0;
	if (SUCCEEDED(dxgiOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &displayCount, nullptr)))
	{
		DXGI_MODE_DESC* displayModes = NewByArray<DXGI_MODE_DESC>(displayCount);
		if (SUCCEEDED(dxgiOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &displayCount, displayModes)))
		{
			mDisplayData.reserve(displayCount);
			for (uint32 index = 0; index < displayCount; ++index)
			{
				const uint32 tempWidth = displayModes[index].Width;
				const uint32 tempHeight = displayModes[index].Height;
				const uint32 tempNumerator = displayModes[index].RefreshRate.Numerator;
				const uint32 tempDenominator = displayModes[index].RefreshRate.Denominator;
				const double tempRefreshRate = static_cast<double>(tempNumerator) / static_cast<double>(tempDenominator);

				mDisplayData.emplace_back(tempWidth, tempHeight, tempNumerator, tempDenominator, tempRefreshRate);
			}
		}
		DeleteByArray(displayModes);
	}
	dxgiOutput->Release();
	dxgiOutput = nullptr;
}

bool Renderer::CreateDevice()
{
	HRESULT handleResult = S_OK;
	const uint32 createDeviceFlags = 0;

	DetectAdapter();

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	const UINT numFeatureLevels = sizeof(featureLevels) / sizeof(D3D_FEATURE_LEVEL);

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

	return true;
}

bool Renderer::CreateSwapChain()
{
	HRESULT handleResult = S_OK;
	
	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = static_cast<uint32>(mStorage->mWindowData.ScreenWidth);
	swapChainDesc.BufferDesc.Height = static_cast<uint32>(mStorage->mWindowData.ScreenHeight);
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = mStorage->mWindowData.Handle;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = true;

	IDXGIFactory* dxgiFactory = nullptr;
	handleResult = mAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory));
	if (FAILED(handleResult))
	{
		return false;
	}
	
	handleResult = dxgiFactory->CreateSwapChain(mDevice, &swapChainDesc, &mSwapChain);
	dxgiFactory->Release();
	dxgiFactory = nullptr;
	if (FAILED(handleResult))
	{
		return false;
	}

	ID3D11Texture2D* backBuffer = nullptr;
	handleResult = mSwapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
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

	return true;
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
