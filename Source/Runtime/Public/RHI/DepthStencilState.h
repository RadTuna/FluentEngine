#pragma once

// External Include
#include <memory>

// Engine Include
#include "D3D11/D3D11DepthStencilState.h"
#include "Core/Core.h"


namespace Fluent
{

	class DepthStencilState :
#ifdef API_GRAPHICS_D3D11
		public D3D11DepthStencilState
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

		[[nodiscard]]
		bool GetUseDepthTest() const { return mbUseDepthTest; }
		[[nodiscard]]
		bool GetUseDepthWrite() const { return mbUseDepthWrite; }
		[[nodiscard]]
		bool GetUseStencil() const { return mbUseStencil; }
		
	private:

		bool mbUseDepthTest = true;
		bool mbUseDepthWrite = true;
		bool mbUseStencil = false;
		
	};
	
}
