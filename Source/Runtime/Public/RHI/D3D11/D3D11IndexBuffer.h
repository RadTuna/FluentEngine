#pragma once

#ifdef API_GRAPHICS_D3D11

// Engine Include
#include "D3D11Definition.h"


namespace Fluent
{

	class D3D11IndexBuffer
	{
	public:

		explicit D3D11IndexBuffer() = default;
		virtual ~D3D11IndexBuffer() = default;


		[[nodiscard]]
		ID3D11Buffer* GetIndexBuffer() const { return mIndexBuffer; }
		
	protected:

		ID3D11Buffer* mIndexBuffer = nullptr;
		
	};

}

#endif
