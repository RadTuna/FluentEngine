
#ifdef API_GRAPHICS_D3D11

// Primary Include
#include "RHI/Device.h"


namespace Fluent
{
	Device::Device() noexcept
	{
		const u32 createDeviceFlags = 0;

		DetectAdapter();

		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
		};
		const UINT numFeatureLevels = sizeof(featureLevels) / sizeof(D3D_FEATURE_LEVEL);

		const D3D_DRIVER_TYPE driverType = mAdapter ? D3D_DRIVER_TYPE_UNKNOWN : D3D_DRIVER_TYPE_HARDWARE;
		
		const HRESULT result = D3D11CreateDevice(
			mAdapter,
			driverType,
			nullptr,
			createDeviceFlags,
			featureLevels,
			numFeatureLevels,
			D3D11_SDK_VERSION,
			&mDevice,
			nullptr,
			&mDeviceContext);

		if (SUCCEEDED(result))
		{
			mbIsInitialized = true;
		}
	}

	Device::~Device() noexcept
	{
		D3D11Release(mDeviceContext);
		D3D11Release(mDevice);
		D3D11Release(mAdapter);
	}

	void Device::DetectAdapter()
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
		mDeviceData.Memory = static_cast<u32>(adapterDesc.DedicatedVideoMemory / 1024 / 1024);


		// Get primary monitor (connected graphic card, num 0)
		IDXGIOutput* dxgiOutput = nullptr;
		result = adapter->EnumOutputs(0, &dxgiOutput);
		if (FAILED(result))
		{
			return;
		}

		u32 displayCount = 0;
		if (SUCCEEDED(dxgiOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &displayCount, nullptr)))
		{
			DXGI_MODE_DESC* displayModes = NewByArray<DXGI_MODE_DESC>(displayCount);
			if (SUCCEEDED(dxgiOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &displayCount, displayModes)))
			{
				mDisplayData.reserve(displayCount);
				for (u32 index = 0; index < displayCount; ++index)
				{
					const u32 tempWidth = displayModes[index].Width;
					const u32 tempHeight = displayModes[index].Height;
					const u32 tempNumerator = displayModes[index].RefreshRate.Numerator;
					const u32 tempDenominator = displayModes[index].RefreshRate.Denominator;
					const f64 tempRefreshRate = static_cast<f64>(tempNumerator) / static_cast<f64>(tempDenominator);

					mDisplayData.emplace_back(tempWidth, tempHeight, tempNumerator, tempDenominator, tempRefreshRate);
				}
			}
			DeleteByArray(displayModes);
		}
		dxgiOutput->Release();
		dxgiOutput = nullptr;
	}

	
}

#endif
