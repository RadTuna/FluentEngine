
#ifdef API_GRAPHICS_D3D11

// Primary Include
#include "RHI/Sampler.h"

// Engine Include
#include "RHI/Device.h"


namespace Fluent
{

	Sampler::Sampler(
		const std::shared_ptr<Device>& device,
		ESamplerFilter minFilter, 
		ESamplerFilter magFilter, 
		ESamplerFilter mipFilter, 
		ESamplerAddressMode addressMode, 
		EComparisonFunction comparison, 
		bool bEnableAnisotropy, 
		bool bEnableComparison) noexcept
	{
		Assert(device && device->IsInitialized());

		mMinFilter = minFilter;
		mMagFilter = magFilter;
		mMipFilter = mipFilter;
		mAddressMode = addressMode;
		mComparisonFunction = comparison;
		mbEnableAnisotropy = bEnableAnisotropy;
		mbEnableComparison = bEnableComparison;
		
		D3D11_SAMPLER_DESC samplerDesc;
		samplerDesc.Filter = ToD3D11Filter(minFilter, magFilter, mipFilter, bEnableAnisotropy, bEnableComparison);
		samplerDesc.AddressU = ToD3D11AddressMode(addressMode);
		samplerDesc.AddressV = ToD3D11AddressMode(addressMode);
		samplerDesc.AddressW = ToD3D11AddressMode(addressMode);
		samplerDesc.MipLODBias = 0.0f;
		samplerDesc.MaxAnisotropy = 0; // temp
		samplerDesc.ComparisonFunc = ToD3D11ComparisonFunction(comparison);
		samplerDesc.BorderColor[0] = 0.0f;
		samplerDesc.BorderColor[1] = 0.0f;
		samplerDesc.BorderColor[2] = 0.0f;
		samplerDesc.BorderColor[3] = 0.0f;
		samplerDesc.MinLOD = FLT_MIN;
		samplerDesc.MaxLOD = FLT_MAX;

		const HRESULT result = device->GetDevice()->CreateSamplerState(&samplerDesc, &mSamplerState);
		Assert(SUCCEEDED(result));
	}

	Sampler::~Sampler() noexcept
	{
		D3D11Release(mSamplerState);
	}
}

#endif
