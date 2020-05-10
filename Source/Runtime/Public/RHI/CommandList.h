#pragma once

// External Include
#include <memory>
#include <vector>

// Engine Include
#include "D3D11/D3D11CommandList.h"
#include "Core/Core.h"
#include "Math/Rectangle.h"


namespace Fluent
{
	
	class CommandList final :
#ifdef API_GRAPHICS_D3D11
		public D3D11CommandList
#endif
	{
	public:

		explicit CommandList(const std::shared_ptr<Device>& device) noexcept;
		virtual ~CommandList() noexcept;


		void Execute();

		void ClearRenderTargetAndDepth(std::vector<Vector4>& clearColor, f32 clearDepth) const;

		void Draw(u32 vertexCount, u32 vertexOffset = 0) const;
		void DrawIndexed(u32 indexCount, u32 indexOffset = 0, u32 vertexOffset = 0) const;

		void SetVertexShader(const std::shared_ptr<Shader>& vertexShader) const;
		void SetPixelShader(const std::shared_ptr<Shader>& pixelShader) const;
		void SetDepthStencilState(const std::shared_ptr<DepthStencilState>& depthStencilState) const;
		void SetRasterizerState(const std::shared_ptr<RasterizerState>& rasterizerState) const;
		void SetBlendState(const std::shared_ptr<BlendState>& blendState) const;
		void SetPrimitiveTopology(EPrimitiveTopology topology) const;
		void SetRenderTargets(const std::vector<std::shared_ptr<Texture2D>>& renderTargets, const std::shared_ptr<Texture2D>& depthStencil) const;
		void SetSwapChainBuffer(const std::shared_ptr<SwapChain>& swapChain, const std::shared_ptr<Texture2D>& depthStencil) const;
		void SetScissorRectangle(const Rectangle& rectangle) const;
		void SetVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) const;
		void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) const;
		void SetConstantBuffer(u32 slot, EShaderType shaderType, const std::shared_ptr<ConstantBuffer>& constantBuffer) const;
		void SetViewport(const Viewport& viewport) const;
		void SetTexture(u32 slot, EShaderType shaderType, const std::shared_ptr<Texture2D>& texture) const;
		void SetSampler(u32 slot, const std::shared_ptr<Sampler>& sampler) const;

	private:

		bool mbIsInitialized = false;
		
	};
	
}
