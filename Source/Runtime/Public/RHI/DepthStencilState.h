#pragma once

// External Include
#include <memory>

// Engine Include
#include "D3D11/D3DDepthStencilState.h"


namespace Fluent
{

	class DepthStencilState :
#ifdef API_GRAPHICS_D3D11
		public D3DDepthStencilState
#endif
	{
	public:

		explicit DepthStencilState(
			const std::shared_ptr<Device>& device,
			bool bUseDepthTest,
			bool bUseDepthWrite,
			bool bUseStencil
			) noexcept;

		virtual ~DepthStencilState() noexcept;
		
	private:

		bool mbUseDepthTest = true;
		bool mbUseDepthWrite = true;
		bool mbUseStencil = false;
		
	};
	
}
