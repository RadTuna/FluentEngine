#pragma once

// External Include
#include <memory>

// Engine Include
#include "D3D11/D3D11SwapChain.h"
#include "Core/Core.h"


namespace Fluent
{
	
	struct WindowData;
	
	class SwapChain final :
#ifdef API_GRAPHICS_D3D11
		public D3D11SwapChain
#endif
	{
	public:

		explicit SwapChain(const std::shared_ptr<Device>& device, const WindowData& winData) noexcept;
		virtual ~SwapChain() noexcept;
		
		bool Present() const;

		[[nodiscard]]
		bool IsInitialized() const { return mbIsInitialized; }
		
	private:
		
		bool mbIsInitialized = false;
		u32 mSyncInterval = 0;
		u32 mFlags = 0;
		
	};
	
}
