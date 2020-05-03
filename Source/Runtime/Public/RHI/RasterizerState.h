#pragma once

// External Include
#include <memory>

// Engine Include
#include "D3D11/D3D11RasterizerState.h"
#include "Core/Core.h"


namespace Fluent
{
	
	class RasterizerState final :
#ifdef API_GRAPHICS_D3D11
		public D3D11RasterizerState
#endif
	{
	public:

		explicit RasterizerState(
			const std::shared_ptr<Device>& device,
			ERenderCullMode cullMode,
			ERenderFillMode fillMode,
			bool bUseDepthClip,
			bool bUseScissor,
			bool bUseMultiSample,
			bool bUseAntialiasedLine) noexcept;

		virtual ~RasterizerState() noexcept;

	private:

		ERenderCullMode mCullMode = ERenderCullMode::Unknown;
		ERenderFillMode mFillMode = ERenderFillMode::Unknown;
		bool mbUseDepthClip = false;
		bool mbUseScissor = false;
		bool mbUseMultiSample = false;
		bool mbUseAntialiasedLine = false;
		
	};
	
}
