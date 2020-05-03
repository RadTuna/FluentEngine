#pragma once

// External Include
#include <memory>

// Engine Include
#include "D3D11/D3D11BlendState.h"
#include "Core/Core.h"


namespace Fluent
{

	class BlendState final :
#ifdef API_GRAPHICS_D3D11
		public D3D11BlendState
#endif
	{
	public:

		explicit BlendState(const std::shared_ptr<Device>& device, bool bIsEnable, 
			ERenderBlend srcBlend, ERenderBlend destBlend, ERenderBlendOperation blendOp,
			ERenderBlend srcBlendAlpha, ERenderBlend destBlendAlpha, ERenderBlendOperation blendOpAlpha) noexcept;
		virtual ~BlendState() = default;

	private:

		bool mbIsBlendEnable = false;
		ERenderBlend mSourceBlend;
		ERenderBlend mDestBlend;
		ERenderBlendOperation mColorBlendOperation;
		ERenderBlend mSourceBlendAlpha;
		ERenderBlend mDestBlendAlpha;
		ERenderBlendOperation mAlphaBlendOperation;
		
	};
	
}
