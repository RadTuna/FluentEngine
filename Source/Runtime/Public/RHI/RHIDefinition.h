#pragma once

#ifdef API_GRAPHICS_D3D11

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <d3d11_1.h>
#include <Windows.h>

#endif


namespace Fluent
{
	
	class CommandList;
	class ConstantBuffer;
	class Device;
	class IndexBuffer;
	class InputLayout;
	class PixelShader;
	class RasterizerState;
	class SwapChain;
	class Vertex;
	class VertexBuffer;
	class VertexShader;
	class Viewport;
	
}
