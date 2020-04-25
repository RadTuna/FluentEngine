#pragma once

#ifdef API_GRAPHICS_D3D11

// Engine Include
#include "D3D11Definition.h"


namespace Fluent
{
	
	class D3D11ConstantBuffer
	{
	public:

		D3D11ConstantBuffer() = default;
		virtual ~D3D11ConstantBuffer() = default;
		
		[[nodiscard]]
		ID3D11Buffer* GetConstantBuffer() const { return mConstantBuffer; }

	protected:

		ID3D11Device* mDevice = nullptr;
		ID3D11DeviceContext* mDeviceContext = nullptr;
		
		ID3D11Buffer* mConstantBuffer = nullptr;

	};

}

#endif
