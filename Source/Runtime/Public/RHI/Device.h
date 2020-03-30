#pragma once

// External Include
#include <vector>

// Engine Include
#include "D3D11/D3D11Device.h"
#include "Core/Core.h"


namespace Fluent
{
	
	class Device final :
#ifdef API_GRAPHICS_D3D11
		public D3D11Device
#endif
	{
	public:

		explicit Device() noexcept;
		virtual ~Device() noexcept;
		
		[[nodiscard]]
		bool IsInitialized() const { return mbIsInitialized; }
		
	private:

		void DetectAdapter();

	private:

		PhysicalDeviceData mDeviceData;
		std::vector<DisplayMode> mDisplayData;

		bool mbIsInitialized = false;

	};

}
