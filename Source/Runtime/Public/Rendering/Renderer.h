#pragma once

// External Include
#include <vector>
#include <memory>

// Engine Include
#include "Core/Core.h"
#include "Core/ISubModule.h"
#include "RendererDefinition.h"
#include "RHI/RHIDefinition.h"


namespace Fluent
{

	class Renderer final : public ISubModule
	{
	public:
		
		explicit Renderer(const std::shared_ptr<EngineStorage>& inStorage) noexcept;
		virtual ~Renderer() noexcept;

		
		// ISubModule functions
		bool Initialize() override;
		void Update(float deltaTime) override;

		bool IsInitialized() const { return mbIsInitialized; }

	private:
		
		void CreateConstantBuffers();
		void CreateShaders();
		void CreateDepthStencilStates();
		void CreateRasterizerStates();
		void CreateRenderTargets();
		void CreateCommandLists();
		
	private:

		// Core
		std::shared_ptr<Device> mDevice;
		std::shared_ptr<SwapChain> mSwapChain;

		// CommandLists // SingleThread == 1
		std::vector<std::shared_ptr<CommandList>> mCommandLists;
		
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
