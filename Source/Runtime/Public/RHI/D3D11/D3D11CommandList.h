#pragma once

#ifdef API_GRAPHICS_D3D11

// Engine Include
#include "D3D11Definition.h"


namespace Fluent
{

	class D3D11CommandList
	{
	public:

		explicit D3D11CommandList() = default;
		virtual ~D3D11CommandList() = default;

	protected:

		ID3D11DeviceContext* mDeviceContext = nullptr;
		
		ID3D11DeviceContext* mDeferredContext = nullptr;
		ID3D11CommandList* mCommandList = nullptr;

	};

}

#endif
