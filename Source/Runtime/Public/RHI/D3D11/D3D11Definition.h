#pragma once

#ifdef API_GRAPHICS_D3D11

#include "RHI/RHIDefinition.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <d3d11_1.h>
#include <Windows.h>

namespace Fluent
{

	inline void D3D11Release(IUnknown* object)
	{
		if (object)
		{
			object->Release();
			object = nullptr;
		}
	}
	
}

#endif
