#pragma once

#ifdef API_GRAPHICS_D3D11

// Engine Include
#include "D3DDefinition.h"


namespace Fluent
{

	class D3DVertexBuffer
	{
	public:

		explicit D3DVertexBuffer() = default;
		virtual ~D3DVertexBuffer() = default;

		
		[[nodiscard]]
		ID3D11Buffer* GetVertexBuffer() const { return mVertexBuffer; }
		
	protected:

		ID3D11Buffer* mVertexBuffer = nullptr;

	};
	
}

#endif
