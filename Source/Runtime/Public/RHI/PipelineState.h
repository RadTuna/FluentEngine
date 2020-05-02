#pragma once

// External Include
#include <vector>
#include <memory>

// Engine Include
#include "D3D11/D3D11PipelineState.h"
#include "Core/Core.h"
#include "RHI/Viewport.h"


namespace Fluent
{

	class PipelineState final :
#ifdef API_GRAPHICS_D3D11
		public D3D11PipelineState
#endif
	{
	public:

		explicit PipelineState() = default;
		virtual ~PipelineState() = default;

		
		void CreatePipelineState(
			const std::shared_ptr<Device>& device,
			const std::shared_ptr<Shader>& vertexShader,
			const std::shared_ptr<Shader>& pixelShader,
			const std::shared_ptr<RasterizerState>& rasterizerState,
			const std::shared_ptr<DepthStencilState>& depthStencilState,
			const InputLayout& inputLayout,
			const Viewport& viewport,
			EPrimitiveTopology topology,
			const std::vector<std::shared_ptr<Texture2D>>& renderTargets,
			const std::shared_ptr<Texture2D>& depthStencilTexture);

	public:

		std::vector<std::shared_ptr<Texture2D>> mRenderTargetTextures;
		std::shared_ptr<Texture2D> mDepthStencilTexture = nullptr;
		Viewport mViewport;
		EPrimitiveTopology mPrimitiveTopology = EPrimitiveTopology::Unknown;

	};

}
