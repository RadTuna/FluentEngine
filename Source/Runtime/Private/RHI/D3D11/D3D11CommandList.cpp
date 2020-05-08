
#ifdef API_GRAPHICS_D3D11

// Primary Include
#include "RHI/CommandList.h"

// Engine Include
#include "RHI/Device.h"
#include "RHI/Texture2D.h"
#include "RHI/VertexBuffer.h"
#include "RHI/IndexBuffer.h"
#include "RHI/ConstantBuffer.h"
#include "RHI/Shader.h"
#include "RHI/DepthStencilState.h"
#include "RHI/RasterizerState.h"
#include "RHI/BlendState.h"


namespace Fluent
{

	CommandList::CommandList(const std::shared_ptr<Device>& device) noexcept
	{
		Assert(device && device->IsInitialized());

		mDeviceContext = device->GetDeviceContext();

		const HRESULT result = device->GetDevice()->CreateDeferredContext(0, &mDeferredContext);
		Assert(SUCCEEDED(result));
	}

	void CommandList::Execute()
	{
		Assert(mDeviceContext != nullptr);

		mDeviceContext->ExecuteCommandList(mCommandList, false);
		D3D11Release(mCommandList);
	}

	void CommandList::Draw(u32 vertexCount, u32 vertexOffset) const
	{
		mDeferredContext->Draw(vertexCount, vertexOffset);

		Assert(mCommandList == nullptr);
		mDeferredContext->FinishCommandList(false, const_cast<ID3D11CommandList**>(&mCommandList));
	}

	void CommandList::DrawIndexed(u32 indexCount, u32 indexOffset, u32 vertexOffset) const
	{
		mDeferredContext->DrawIndexed(indexCount, indexOffset, vertexOffset);

		Assert(mCommandList == nullptr);
		mDeferredContext->FinishCommandList(false, const_cast<ID3D11CommandList**>(&mCommandList));
	}

	void CommandList::SetVertexShader(const std::shared_ptr<Shader>& vertexShader) const
	{
		Assert(vertexShader->GetVertexShader() != nullptr);
		Assert(vertexShader->GetInputLayout() != nullptr);

		mDeferredContext->VSSetShader(vertexShader->GetVertexShader(), nullptr, 0);
		mDeferredContext->IASetInputLayout(vertexShader->GetInputLayout());
	}

	void CommandList::SetPixelShader(const std::shared_ptr<Shader>& pixelShader) const
	{
		Assert(pixelShader->GetPixelShader() != nullptr);

		mDeferredContext->PSSetShader(pixelShader->GetPixelShader(), nullptr, 0);
	}

	void CommandList::SetDepthStencilState(const std::shared_ptr<DepthStencilState>& depthStencilState) const
	{
		Assert(depthStencilState->GetDepthStencilState() != nullptr);

		mDeferredContext->OMSetDepthStencilState(depthStencilState->GetDepthStencilState(), 1);
	}

	void CommandList::SetRasterizerState(const std::shared_ptr<RasterizerState>& rasterizerState) const
	{
		Assert(rasterizerState->GetRasterizerState() != nullptr);

		mDeferredContext->RSSetState(rasterizerState->GetRasterizerState());
	}

	void CommandList::SetBlendState(const std::shared_ptr<BlendState>& blendState) const
	{
		Assert(blendState->GetBlendState() != nullptr);
		
		const f32 commonBlendFactor = blendState->GetBlendFactor();
		f32 blendFactors[4] = { commonBlendFactor, };
	
		mDeferredContext->OMSetBlendState(blendState->GetBlendState(), blendFactors, 0xFFFFFFFF);
	}

	void CommandList::SetPrimitiveTopology(EPrimitiveTopology topology) const
	{	
		const D3D11_PRIMITIVE_TOPOLOGY d3dTopology = ToD3D11Topology(topology);
		
		mDeferredContext->IASetPrimitiveTopology(d3dTopology);
	}

	void CommandList::SetRenderTarget(const std::vector<std::shared_ptr<Texture2D>>& renderTargets,
		const std::shared_ptr<Texture2D>& depthStencil) const
	{
		Assert(depthStencil->GetDepthStencilView() != nullptr);
		
		const u32 renderTargetNum = static_cast<u32>(renderTargets.size());
		std::vector<ID3D11RenderTargetView*> d3dRenderTargets;
		d3dRenderTargets.reserve(renderTargetNum);
		for (u32 index = 0; index < renderTargetNum; ++index)
		{
			ID3D11RenderTargetView* tempRTV = renderTargets[index]->GetRenderTargetView();
			Assert(tempRTV != nullptr);
			
			d3dRenderTargets.emplace_back(tempRTV);
		}
		
		mDeferredContext->OMSetRenderTargets(renderTargetNum, d3dRenderTargets.data(), depthStencil->GetDepthStencilView());
	}

	void CommandList::SetScissorRectangle(const Rectangle& rectangle) const
	{
		D3D11_RECT scissorRect = {
			static_cast<i32>(rectangle.MinX), static_cast<i32>(rectangle.MinY),
			static_cast<i32>(rectangle.MaxX), static_cast<i32>(rectangle.MaxY) };

		mDeferredContext->RSSetScissorRects(1, &scissorRect);
	}

	void CommandList::SetVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) const
	{
		Assert(vertexBuffer->GetVertexBuffer() != nullptr);

		ID3D11Buffer* tempVertexBuffer = vertexBuffer->GetVertexBuffer();
		const u32 stride = vertexBuffer->GetStride();
		mDeferredContext->IASetVertexBuffers(0, 1, &tempVertexBuffer, &stride, nullptr);
	}

	void CommandList::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) const
	{
		Assert(indexBuffer->GetIndexBuffer() != nullptr);

		const u32 stride = indexBuffer->GetStride();
		DXGI_FORMAT indexBufferFormat = DXGI_FORMAT_R32_UINT;
		switch (stride) 
		{
		case 8:
			indexBufferFormat = DXGI_FORMAT_R8_UINT;
			break;
		case 16:
			indexBufferFormat = DXGI_FORMAT_R16_UINT;
			break;
		case 32:
			indexBufferFormat = DXGI_FORMAT_R32_UINT;
			break;
		default:
			Assert(false);
			break;
		}

		mDeferredContext->IASetIndexBuffer(indexBuffer->GetIndexBuffer(), indexBufferFormat, 0);
	}

	void CommandList::SetConstantBuffer(u32 slot, EShaderType shaderType, const std::shared_ptr<ConstantBuffer>& constantBuffer) const
	{
		Assert(shaderType != EShaderType::Unknown && shaderType != EShaderType::Compute);
		Assert(constantBuffer->GetConstantBuffer() != nullptr);

		ID3D11Buffer* tempConstantBuffer = constantBuffer->GetConstantBuffer();
		if (shaderType == EShaderType::Vertex)
		{
			mDeferredContext->VSSetConstantBuffers(slot, 1, &tempConstantBuffer);
		}
		else if (shaderType == EShaderType::Pixel)
		{
			mDeferredContext->PSSetConstantBuffers(slot, 1, &tempConstantBuffer);
		}
	}

	void CommandList::SetViewport(const Viewport& viewport) const
	{
		D3D11_VIEWPORT d3dViewport;
		d3dViewport.TopLeftX = viewport.X;
		d3dViewport.TopLeftY = viewport.Y;
		d3dViewport.Width = viewport.Width;
		d3dViewport.Height = viewport.Height;
		d3dViewport.MinDepth = viewport.Near;
		d3dViewport.MaxDepth = viewport.Far;
		
		mDeferredContext->RSSetViewports(1, &d3dViewport);
	}

	void CommandList::SetTexture(u32 slot, EShaderType shaderType, const std::shared_ptr<Texture2D>& texture) const
	{
		Assert(shaderType != EShaderType::Unknown && shaderType != EShaderType::Compute);
		Assert(texture->GetShaderResourceView() != nullptr);
		
		ID3D11ShaderResourceView* tempSRV = texture->GetShaderResourceView();
		if (shaderType == EShaderType::Vertex)
		{
			mDeferredContext->VSSetShaderResources(slot, 1, &tempSRV);
		}
		else if (shaderType == EShaderType::Pixel)
		{
			mDeferredContext->PSSetShaderResources(slot, 1, &tempSRV);
		}
	}
	
}

#endif
