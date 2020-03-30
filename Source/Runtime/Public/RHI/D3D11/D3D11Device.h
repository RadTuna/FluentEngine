#pragma once

#ifdef API_GRAPHICS_D3D11

// Engine Include
#include "D3D11Definition.h"


namespace Fluent
{
	
	class D3D11Device
	{
	public:

		D3D11Device() = default;
		virtual ~D3D11Device() = default;
		
		[[nodiscard]]
		IDXGIAdapter* GetAdapter() const { return mAdapter; };

		[[nodiscard]]
		ID3D11Device* GetDevice() const { return mDevice; }

		[[nodiscard]]
		ID3D11DeviceContext* GetDeviceContext() const { return mDeviceContext; }

	protected:

		IDXGIAdapter* mAdapter = nullptr;
		ID3D11Device* mDevice = nullptr;
		ID3D11DeviceContext* mDeviceContext = nullptr;

	};

}

#endif
