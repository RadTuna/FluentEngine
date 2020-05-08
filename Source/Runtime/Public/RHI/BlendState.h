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
			ERenderBlend srcBlendAlpha, ERenderBlend destBlendAlpha, ERenderBlendOperation blendOpAlpha,
			f32 blendFactor) noexcept;
		virtual ~BlendState() = default;

		
		[[nodiscard]]
		ERenderBlend GetSourceBlend() const { return mSourceBlend; }
		
		[[nodiscard]]
		ERenderBlend GetDestinationBlend() const { return mDestBlend; }

		[[nodiscard]]
		ERenderBlendOperation GetColorBlendOperation() const { return mColorBlendOperation; }

		[[nodiscard]]
		ERenderBlend GetSourceAlphaBlend() const { return mSourceAlphaBlend; }

		[[nodiscard]]
		ERenderBlend GetDestinationAlphaBlend() const { return mDestAlphaBlend; }

		[[nodiscard]]
		ERenderBlendOperation GetAlphaBlendOperation() const { return mAlphaBlendOperation; }
		
		[[nodiscard]]
		f32 GetBlendFactor() const { return mBlendFactor; }

	private:

		bool mbIsBlendEnable = false;
		ERenderBlend mSourceBlend;
		ERenderBlend mDestBlend;
		ERenderBlendOperation mColorBlendOperation;
		ERenderBlend mSourceAlphaBlend;
		ERenderBlend mDestAlphaBlend;
		ERenderBlendOperation mAlphaBlendOperation;
		f32 mBlendFactor = 0.0f;
		
	};
	
}
