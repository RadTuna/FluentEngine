#pragma once

#include "RHI/RHIDefinition.h"

#ifdef API_GRAPHICS_D3D11

#include <DirectXMath.h>

namespace Fluent
{

	struct D3DBufferCommon
	{
		DirectX::XMFLOAT4X4 WorldMatrix;
		DirectX::XMFLOAT4X4 ViewMatrix;
		DirectX::XMFLOAT4X4 ProjectionMatrix;
	};
	
	class D3DConstantBuffer
	{
	public:

		D3DConstantBuffer() = default;
		virtual ~D3DConstantBuffer() = default;
		
		[[nodiscard]]
		ID3D11Buffer* GetBuffer() const { return mBuffer; }

	protected:

		ID3D11Buffer* mBuffer = nullptr;

	};

}

#endif
