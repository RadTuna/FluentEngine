#pragma once

#ifdef API_GRAPHICS_D3D11

// Engine Include
#include "D3D11Definition.h"


namespace Fluent
{

	class D3D11Sampler
	{
	public:

		explicit D3D11Sampler() = default;
		virtual ~D3D11Sampler() = default;


		[[nodiscard]]
		ID3D11SamplerState* GetSamplerState() const { return mSamplerState; }
		
	protected:

		ID3D11SamplerState* mSamplerState = nullptr;
		
	};
	
}

#endif
