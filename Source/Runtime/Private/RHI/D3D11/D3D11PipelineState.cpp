
#ifdef API_GRAPHICS_D3D11

// Primary Include
#include "RHI/PipelineState.h"

// Engine Include
#include "RHI/Device.h"
#include "RHI/Shader.h"
#include "RHI/RasterizerState.h"
#include "RHI/DepthStencilState.h"


namespace Fluent
{

	void PipelineState::CreatePipelineState(
		const std::shared_ptr<Device>& device,
		const std::shared_ptr<Shader>& vertexShader, 
		const std::shared_ptr<Shader>& pixelShader, 
		const std::shared_ptr<RasterizerState>& rasterizerState, 
		const std::shared_ptr<DepthStencilState>& depthStencilState, 
		const InputLayout& inputLayout, 
		const Viewport& viewport, 
		EPrimitiveTopology topology, 
		const std::vector<std::shared_ptr<Texture2D>>& renderTargets, 
		const std::shared_ptr<Texture2D>& depthStencilTexture)
	{
		Assert(device && device->IsInitialized());
		
		mRenderTargetTextures = renderTargets;
		mDepthStencilTexture = depthStencilTexture;
		mViewport = viewport;
		mPrimitiveTopology = topology;

		mVertexShader = vertexShader->GetVertexShader();
		Assert(mVertexShader != nullptr);

		mPixelShader = pixelShader->GetPixelShader();
		Assert(mPixelShader != nullptr);

		mRasterizerState = rasterizerState->GetRasterizerState();
		Assert(mRasterizerState != nullptr);

		mDepthStencilState = depthStencilState->GetDepthStencilState();
		Assert(mDepthStencilState != nullptr);
		
	}

	
}

#endif
