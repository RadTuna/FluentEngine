#pragma once

#ifdef API_GRAPHICS_D3D11

// Primary Include
#include "RHI/BlendState.h"

// Engine Include
#include "RHI/Device.h"

namespace Fluent
{

	BlendState::BlendState(const std::shared_ptr<Device>& device, bool bIsEnable, 
		ERenderBlend srcBlend, ERenderBlend destBlend, ERenderBlendOperation blendOp, 
		ERenderBlend srcBlendAlpha, ERenderBlend destBlendAlpha, ERenderBlendOperation blendOpAlpha,
		f32 blendFactor) noexcept
	{
		Assert(device && device->IsInitialized());

		mbIsBlendEnable = bIsEnable;
		mSourceBlend = srcBlend;
		mDestBlend = destBlend;
		mColorBlendOperation = blendOp;
		mSourceAlphaBlend = srcBlendAlpha;
		mDestAlphaBlend = destBlendAlpha;
		mAlphaBlendOperation = blendOpAlpha;
		mBlendFactor = blendFactor;

		D3D11_BLEND_DESC blendDesc = { 0, };
		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = bIsEnable;
		for (D3D11_RENDER_TARGET_BLEND_DESC& rtBlend : blendDesc.RenderTarget)
		{
			rtBlend.BlendEnable = bIsEnable;
			rtBlend.SrcBlend = ToD3D11Blend(srcBlend);
			rtBlend.DestBlend = ToD3D11Blend(destBlend);
			rtBlend.BlendOp = ToD3D11BlendOp(blendOp);
			rtBlend.SrcBlendAlpha = ToD3D11Blend(srcBlendAlpha);
			rtBlend.DestBlendAlpha = ToD3D11Blend(destBlendAlpha);
			rtBlend.BlendOpAlpha = ToD3D11BlendOp(blendOpAlpha);
			rtBlend.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		}

		const HRESULT result = device->GetDevice()->CreateBlendState(&blendDesc, &mBlendState);
		Assert(SUCCEEDED(result));
		
	}

	BlendState::~BlendState() noexcept
	{
		D3D11Release(mBlendState);
	}
}

#endif
