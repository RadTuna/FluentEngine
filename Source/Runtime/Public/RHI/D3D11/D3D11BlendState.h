#pragma once

#ifdef API_GRAPHICS_D3D11

// Engine Include
#include "D3D11Definition.h"


namespace Fluent
{

	class D3D11BlendState
	{
	public:

		explicit D3D11BlendState() = default;
		virtual ~D3D11BlendState() = default;


		[[nodiscard]]
		ID3D11BlendState* GetBlendState() const { return mBlendState; }
		
	protected:

		ID3D11BlendState* mBlendState = nullptr;

	};

}

#endif