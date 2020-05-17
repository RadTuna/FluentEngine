#pragma once

// External Include
#include <vector>
#include <memory>

// Engine Include
#include "Core/Core.h"
#include "Core/ISubModule.h"
#include "RendererDefinition.h"
#include "RHI/RHIDefinition.h"
#include "Rendering/Mesh.h"


namespace Fluent
{

	constexpr u32 MAIN_THREAD_INDEX = 0;
	
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
		void CreateRenderResource();

		// Pre-setup state
		void SetupGlobalConstantBufferAndSampler();

		// Update current viewport
		void UpdateViewport();
		
		// Update constant buffers
		void UpdateFrameBuffer();
		
		// Render passes
		void PassSimpleQuad(const std::shared_ptr<CommandList>& commandList);
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

		Mesh mQuadMesh;
		
	};

}
