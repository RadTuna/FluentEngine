#pragma once

#include "D3DDefinition.h"

#ifdef API_GRAPHICS_D3D11

namespace Fluent
{
	
	class D3DConstantBuffer
	{
	public:

		D3DConstantBuffer() = default;
		virtual ~D3DConstantBuffer() = default;
		
		[[nodiscard]]
		ID3D11Buffer* GetConstantBuffer() const { return mConstantBuffer; }

	protected:

		ID3D11Buffer* mConstantBuffer = nullptr;

	};

}

#endif
