#pragma once

// External Include
#include <vector>
#include <memory>

// Engine Include
#include "Core/Core.h"
#include "Core/ISubSystem.h"
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

	private:
		
		void CreateConstantBuffers();
		void CreateVertexShaders();
		void CreatePixelShaders();
		void CreateDepthStencilStates();
		void CreateRasterizerStates();
		void CreateRenderTargets();
		
	private:

		std::shared_ptr<Device> mDevice;
		std::shared_ptr<SwapChain> mSwapChain;

		std::shared_ptr<ConstantBuffer> mCommonConstantBuffer;
		
	};

}
