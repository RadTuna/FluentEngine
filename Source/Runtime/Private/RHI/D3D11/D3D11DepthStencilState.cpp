

#ifdef API_GRAPHICS_D3D11

// Primary Include
#include "RHI/DepthStencilState.h"

// Engine Include
#include "RHI/Device.h"

namespace Fluent
{

	DepthStencilState::DepthStencilState(
		const std::shared_ptr<Device>& device,
		bool bUseDepthTest,
		bool bUseDepthWrite,
		bool bUseStencil) noexcept
	{
		Assert(device && device->IsInitialized());
		mDevice = device->GetDevice();

		mbUseDepthTest = bUseDepthTest;
		mbUseDepthWrite = bUseDepthWrite;
		mbUseStencil = bUseStencil;

		D3D11_DEPTH_STENCIL_DESC depthDesc = {};
		depthDesc.DepthEnable = mbUseDepthTest;
		depthDesc.DepthWriteMask = mbUseDepthWrite ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
		depthDesc.StencilEnable = mbUseStencil;
		depthDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
		depthDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
		depthDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		depthDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depthDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depthDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		depthDesc.BackFace = depthDesc.FrontFace;

		const HRESULT result = mDevice->CreateDepthStencilState(&depthDesc, &mDepthStencilState);
		Assert(SUCCEEDED(result));
	}

	DepthStencilState::~DepthStencilState() noexcept
	{
		D3D11Release(mDepthStencilState);
	}

	
}

#endif