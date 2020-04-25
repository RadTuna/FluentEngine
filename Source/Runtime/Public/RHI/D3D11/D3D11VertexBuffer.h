#pragma once

#ifdef API_GRAPHICS_D3D11

// Engine Include
#include "D3D11Definition.h"


namespace Fluent
{

	class D3D11VertexBuffer
	{
	public:

		explicit D3D11VertexBuffer() = default;
		virtual ~D3D11VertexBuffer() = default;

		
		[[nodiscard]]
		ID3D11Buffer* GetVertexBuffer() const { return mVertexBuffer; }
		
	protected:

		ID3D11Device* mDevice = nullptr;
		ID3D11DeviceContext* mDeviceContext = nullptr;
		
		ID3D11Buffer* mVertexBuffer = nullptr;

	};
	
}

#endif
