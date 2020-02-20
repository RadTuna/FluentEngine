#pragma once

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "comctl32.lib")

#include <Windows.h>
#include <d3d11.h>
#include "Core/Core.h"

namespace Fluent
{

	class Renderer
	{
	public:

		Renderer(HWND winHandle);
		~Renderer();

		void Initialize();
		void Tick();

		void CreateConstantBuffers();
		void CreateShaders();
		void CreateDepthStencilStates();
		void CreateRasterizerStates();
		void CreateRenderTargets();

	private:

		HWND mWindowHandle;

		ID3D11Device* mDevice;
		ID3D11DeviceContext* mDeviceContext;
		IDXGISwapChain* mSwapChain;
		ID3D11RenderTargetView* mRenderTargetView;

	};

}
