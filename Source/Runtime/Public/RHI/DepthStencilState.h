#pragma once

// External Include
#include <memory>

// Engine Include
#include "D3D11/D3DDepthStencilState.h"
#include "Core/Core.h"


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

		[[nodiscard]]
		bool GetUseDepthTest() const { return mbUseDepthTest; }
		[[nodiscard]]
		bool GetUseDepthWrite() const { return mbUseDepthWrite; }
		[[nodiscard]]
		bool GetUseStencil() const { return mbUseStencil; }
		[[nodiscard]]
		bool IsInitialized() const { return mbIsInitialized; }
		
	private:

		std::shared_ptr<Device> mDevice;
		bool mbUseDepthTest = true;
		bool mbUseDepthWrite = true;
		bool mbUseStencil = false;
		bool mbIsInitialized = false;
		
	};
	
}
