#pragma once

// Additional dependencies
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "comctl32.lib")

// External Include
#include <Windows.h>
#include <d3d11.h>
#include <DirectXMath.h>

// Engine Include
#include "Core/Core.h"
#include "Core/ISubSystem.h"


namespace Fluent
{

	class Renderer : public ISubSystem
	{
	public:

		using Super = ISubSystem;
		
		explicit Renderer(const std::shared_ptr<RuntimeStorage>& inStorage) noexcept;
		virtual ~Renderer() noexcept;

		// ISubSystem functions
		bool Initialize() override;
		void Update(float deltaTime) override;

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
