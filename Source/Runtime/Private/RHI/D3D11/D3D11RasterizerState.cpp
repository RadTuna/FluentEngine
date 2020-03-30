
#ifdef API_GRAPHICS_D3D11

// Primary Include
#include "RHI/RasterizerState.h"

// Engine Include
#include "RHI/Device.h"


namespace Fluent
{

	RasterizerState::RasterizerState(
		const std::shared_ptr<Device>& device,
		ERenderCullMode cullMode,
		ERenderFillMode fillMode,
		bool bUseDepthClip,
		bool bUseScissor,
		bool bUseMultiSample,
		bool bUseAntialiasedLine) noexcept
	{
		Assert(device && device->IsInitialized());

		mCullMode = cullMode;
		mFillMode = fillMode;

		mbUseDepthClip = bUseDepthClip;
		mbUseScissor = bUseScissor;
		mbUseMultiSample = bUseMultiSample;
		mbUseAntialiasedLine = bUseAntialiasedLine;

		
		D3D11_RASTERIZER_DESC rasterDesc = {};
		rasterDesc.CullMode = ToD3DCullMode(mCullMode);
		rasterDesc.FillMode = ToD3DFillMode(mFillMode);
		rasterDesc.FrontCounterClockwise = false;
		rasterDesc.DepthBias = 0;
		rasterDesc.DepthBiasClamp = 0.0f;
		rasterDesc.SlopeScaledDepthBias = 0.0f;
		rasterDesc.DepthClipEnable = mbUseDepthClip;
		rasterDesc.MultisampleEnable = mbUseMultiSample;
		rasterDesc.AntialiasedLineEnable = mbUseAntialiasedLine;
		rasterDesc.ScissorEnable = mbUseScissor;

		const HRESULT result = device->GetDevice()->CreateRasterizerState(&rasterDesc, &mRasterizerState);
		if (SUCCEEDED(result))
		{
			mbIsInitialized = true;
		}
		else
		{
			mbIsInitialized = false;
		}
	}

	RasterizerState::~RasterizerState() noexcept
	{
		D3D11Release(mRasterizerState);
	}


	D3D11_CULL_MODE D3D11RasterizerState::ToD3DCullMode(ERenderCullMode cullMode)
	{
		switch (cullMode)
		{
			case ERenderCullMode::None:
			{
				return D3D11_CULL_MODE::D3D11_CULL_NONE;
			}
			case ERenderCullMode::Back:
			{
				return D3D11_CULL_MODE::D3D11_CULL_BACK;
			}
			case ERenderCullMode::Front:
			{
				return D3D11_CULL_MODE::D3D11_CULL_FRONT;
			}
			default:
			{
				Assert(false);
				return D3D11_CULL_MODE::D3D11_CULL_NONE;
			}
		}
	}

	D3D11_FILL_MODE D3D11RasterizerState::ToD3DFillMode(ERenderFillMode fillMode)
	{
		switch (fillMode)
		{
			case ERenderFillMode::Solid:
			{
				return D3D11_FILL_MODE::D3D11_FILL_SOLID;
			}
			case ERenderFillMode::WireFrame:
			{
				return D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
			}
			default:
			{
				Assert(false);
				return D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
			}
		}
	}
	
}

#endif

