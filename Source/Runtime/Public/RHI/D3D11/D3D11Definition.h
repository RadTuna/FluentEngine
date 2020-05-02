#pragma once

#ifdef API_GRAPHICS_D3D11

#include "RHI/RHIDefinition.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <d3d11_1.h>
#include <Windows.h>


#define D3D11Release(Object) \
	D3DRelease(Object); \
	Object = nullptr; \

namespace Fluent
{
	inline void D3DRelease(IUnknown* object)
	{
		if (object != nullptr)
		{
			object->Release();
		}
	}
	
	const static DXGI_FORMAT DxgiFormatMap[] =
	{
		DXGI_FORMAT_UNKNOWN,

		// R
		DXGI_FORMAT_R8_UNORM,
		DXGI_FORMAT_R16_UINT,
		DXGI_FORMAT_R16_FLOAT,
		DXGI_FORMAT_R32_UINT,
		DXGI_FORMAT_R32_FLOAT,
		DXGI_FORMAT_D32_FLOAT,
		DXGI_FORMAT_R32_TYPELESS,

		// RG
		DXGI_FORMAT_R8G8_UNORM,
		DXGI_FORMAT_R16G16_FLOAT,
		DXGI_FORMAT_R32G32_FLOAT,

		// RGB
		DXGI_FORMAT_R32G32B32_FLOAT,

		// RGBA
		DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_FORMAT_R16G16B16A16_FLOAT,
		DXGI_FORMAT_R32G32B32A32_FLOAT
	};
	inline DXGI_FORMAT ToDxgiFormat(EPixelFormat format)
	{
		const u32 index = static_cast<u32>(format);
		return DxgiFormatMap[index];
	}

	const static D3D11_PRIMITIVE_TOPOLOGY TopologyMap[] =
	{
		D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED,
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		D3D11_PRIMITIVE_TOPOLOGY_LINELIST
	};
	inline D3D11_PRIMITIVE_TOPOLOGY ToD3D11Topology(EPrimitiveTopology topology)
	{
		const u32 index = static_cast<u32>(topology);
		return TopologyMap[index];
	}

}

#endif
