#pragma once

#ifdef API_GRAPHICS_D3D11

// Engine Include
#include "D3DDefinition.h"


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
