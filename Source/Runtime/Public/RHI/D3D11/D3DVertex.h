#pragma once

#include "RHI/RHIDefinition.h"

#ifdef API_GRAPHICS_D3D11

#include <DirectXMath.h>

namespace Fluent
{

	struct D3DVertexPos
	{
		DirectX::XMFLOAT4 Position;
	};

	struct D3DVertexPosTex
	{
		DirectX::XMFLOAT4 Position;
		DirectX::XMFLOAT2 TexCoord;
	};
	
}

#endif
