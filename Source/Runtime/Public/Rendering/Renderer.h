#pragma once

// Additional dependencies
#pragma comment (lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment (lib, "d3dcompiler.lib")

// External Include
#include <Windows.h>
#include <d3d11_1.h>
#include <string>
#include <vector>

// Engine Include
#include "Core/Core.h"
#include "Core/ISubSystem.h"


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

	class Renderer : public ISubSystem
	{
	public:

		using Super = ISubSystem;
		
		explicit Renderer(const std::shared_ptr<RuntimeStorage>& inStorage) noexcept;
		virtual ~Renderer() noexcept;

		// ISubSystem functions
		bool Initialize() override;
		void Update(float deltaTime) override;

	private:

		void DetectAdapter();

		bool CreateDevice();
		bool CreateSwapChain();
		
		void CreateConstantBuffers();
		void CreateVertexShaders();
		void CreatePixelShaders();
		void CreateDepthStencilStates();
		void CreateRasterizerStates();
		void CreateRenderTargets();
		
	private:

		// Custom device data
		PhysicalDeviceData mDeviceData;
		std::vector<DisplayMode> mDisplayData;

		// DX core variables
		IDXGIAdapter* mAdapter;
		ID3D11Device* mDevice;
		ID3D11DeviceContext* mDeviceContext;
		IDXGISwapChain* mSwapChain;
		ID3D11RenderTargetView* mRenderTargetView;

		std::vector<ID3D11Buffer*> mConstantBuffers;
		std::vector<ID3D11VertexShader*> mVertexShaders;
		std::vector<ID3D11PixelShader*> mPixelShaders;
		std::vector<ID3D11DepthStencilState*> mDepthStencilStates;
		std::vector<ID3D11RasterizerState*> mRasterizerStates;
		std::vector<ID3D11RenderTargetView*> mRenderTargetViews;
		
	};

}
