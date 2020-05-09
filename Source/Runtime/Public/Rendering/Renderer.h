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

		[[nodiscard]]
		bool IsInitialized() const { return mbIsInitialized; }

	private:

		// Render resource creation
		void CreateConstantBuffers();
		void CreateShaders();
		void CreateDepthStencilStates();
		void CreateRasterizerStates();
		void CreateRenderTargets();
		void CreateBlendState();
		void CreateSampler();
		void CreateCommandLists();

		// Update current viewport
		void UpdateViewport();
		
		// Update constant buffers
		void UpdateFrameBuffer(const std::shared_ptr<CommandList>& commandList);
		
		// Render passes
		void PassGBuffer(const std::shared_ptr<CommandList>& commandList);
		void PassComposition(const std::shared_ptr<CommandList>& commandList);
		
	private:

		// Core
		std::shared_ptr<Device> mDevice;
		std::shared_ptr<SwapChain> mSwapChain;

		// CommandLists // SingleThread == 1
		std::vector<std::shared_ptr<CommandList>> mCommandLists;
		
		std::vector<std::shared_ptr<Texture2D>> mRenderTargets;
		std::shared_ptr<Texture2D> mDepthStencil;
		std::vector<std::shared_ptr<Shader>> mShaders;
		std::vector<std::shared_ptr<DepthStencilState>> mDepthStencilStates;
		std::vector<std::shared_ptr<RasterizerState>> mRasterizerStates;
		std::vector<std::shared_ptr<ConstantBuffer>> mConstantBuffers;
		std::vector<std::shared_ptr<BlendState>> mBlendStates;
		std::vector<std::shared_ptr<Sampler>> mSamplers;

		// Current viewport
		Viewport mViewport;

		// Other
		bool mbIsInitialized = false;

		bool mbIsRendering = false;
	};

}
