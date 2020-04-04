#pragma once

// External Include
#include <vector>
#include <memory>

// Engine Include
#include "Core/Core.h"
#include "Core/ISubSystem.h"
#include "RendererDefinition.h"
#include "RHI/RHIDefinition.h"


namespace Fluent
{

	class Renderer final : public ISubSystem
	{
	public:
		
		explicit Renderer(const std::shared_ptr<RuntimeStorage>& inStorage) noexcept;
		virtual ~Renderer() noexcept;

		
		// ISubSystem functions
		bool Initialize() override;
		void Update(float deltaTime) override;

		bool IsInitialized() const { return mbIsInitialized; }

	private:
		
		void CreateConstantBuffers();
		void CreateShaders();
		void CreateDepthStencilStates();
		void CreateRasterizerStates();
		void CreateRenderTargets();
		
	private:

		// Core
		std::shared_ptr<Device> mDevice;
		std::shared_ptr<SwapChain> mSwapChain;

		// RenderTargets
		std::vector<std::shared_ptr<Texture2D>> mRenderTargets;

		// Shaders
		std::vector<std::shared_ptr<Shader>> mShaders;

		// Depth-stencil state
		std::vector<std::shared_ptr<DepthStencilState>> mDepthStencilStates;

		// Rasterizer state
		std::vector<std::shared_ptr<RasterizerState>> mRasterizerStates;

		// Constant buffer
		std::vector<std::shared_ptr<ConstantBuffer>> mConstantBuffers;

		// Other
		bool mbIsInitialized = false;
	};

}
