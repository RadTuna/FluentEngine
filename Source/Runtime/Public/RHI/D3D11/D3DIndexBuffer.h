#pragma once

#include "D3DDefinition.h"

#ifdef API_GRAPHICS_D3D11

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
