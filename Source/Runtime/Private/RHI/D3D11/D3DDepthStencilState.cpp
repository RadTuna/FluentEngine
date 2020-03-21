

#ifdef API_GRAPHICS_D3D11

#include "RHI/DepthStencilState.h"

namespace Fluent
{

	DepthStencilState::DepthStencilState(
		const std::shared_ptr<Device>& device, 
		bool bUseDepthTest, 
		bool bUseDepthWrite, 
		bool bUseStencil) noexcept
	{
		
	}

	DepthStencilState::~DepthStencilState() noexcept
	{
		if (mDepthStencilState != nullptr)
		{
			mDepthStencilState->Release();
			mDepthStencilState = nullptr;
		}
	}

	
}

#endif