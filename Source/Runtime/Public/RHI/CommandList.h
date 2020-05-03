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
		~CommandList() = default;


		void Execute();

		void Draw(u32 vertexCount, u32 vertexOffset = 0) const;
		void DrawIndexed(u32 indexCount, u32 indexOffset = 0, u32 vertexOffset = 0) const;

		void SetVertexShader(const std::shared_ptr<Shader>& vertexShader) const;
		void SetPixelShader(const std::shared_ptr<Shader>& pixelShader) const;
		void SetInputLayout(const InputLayout& inputLayout) const;
		void SetViewport(const Viewport& viewport);
		void SetDepthStencilState(const std::shared_ptr<DepthStencilState>& depthStencilState);
		void SetRasterizerState(const std::shared_ptr<RasterizerState>& rasterizerState);
		void SetPrimitiveTopology(EPrimitiveTopology topology);
		void SetRenderTarget(const std::vector<std::shared_ptr<Texture2D>>& renderTarget, const std::shared_ptr<Texture2D>& depthStencil);
		void SetScissorRectangle(const Rectangle& rectangle) const;
		void SetVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) const;
		void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) const;
		void SetConstantBuffer(u32 slot, EShaderType shaderType, const std::shared_ptr<ConstantBuffer>& constantBuffer) const;
		void SetViewport(const Viewport& viewport) const;
		void SetTexture(u32 slot, EShaderType shaderType, const std::shared_ptr<Texture2D>& texture) const;

	private:

		bool mbIsInitialized = false;
		
	};
	
}
