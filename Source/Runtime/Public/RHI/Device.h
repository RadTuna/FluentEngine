#pragma once

// External Include
#include <string>
#include <vector>

// Engine Include
#include "D3D11/D3DDevice.h"
#include "Core/Core.h"


namespace Fluent
{

	struct PhysicalDeviceData
	{
		PhysicalDeviceData() = default;
		PhysicalDeviceData(const std::string& name, uint32 mem) : DeviceName(name), Memory(mem) {}

		std::string DeviceName = "Unknown";
		uint32 Memory = 0;
	};

	struct DisplayMode
	{
		DisplayMode() = default;
		DisplayMode(uint32 inWidth, uint32 inHeight, uint32 inNumerator, uint32 inDenominator, double inRefresh)
			: Width(inWidth), Height(inHeight), Numerator(inNumerator), Denominator(inDenominator), RefreshRate(inRefresh) {}

		uint32 Width = 0;
		uint32 Height = 0;
		uint32 Numerator = 0;
		uint32 Denominator = 0;
		double RefreshRate = 0.0;
	};
	
	class Device final :
#ifdef API_GRAPHICS_D3D11
		public D3DDevice
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
