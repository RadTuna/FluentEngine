#pragma once

#ifdef API_GRAPHICS_D3D11

// Engine Include
#include "D3DDefinition.h"


namespace Fluent
{

	class D3DIndexBuffer
	{
	public:

		explicit D3DIndexBuffer() = default;
		virtual ~D3DIndexBuffer() = default;


		[[nodiscard]]
		ID3D11Buffer* GetIndexBuffer() const { return mIndexBuffer; }
		
	protected:

		ID3D11Buffer* mIndexBuffer = nullptr;
		
	};

}

#endif
