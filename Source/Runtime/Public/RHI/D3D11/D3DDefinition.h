#pragma once

#include "RHI/RHIDefinition.h"

#ifdef API_GRAPHICS_D3D11

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <d3d11_1.h>
#include <Windows.h>

namespace Fluent
{

	void D3DRelease(IUnknown* object)
	{
		if (object)
		{
			object->Release();
			object = nullptr;
		}
	}
	
}

#endif
