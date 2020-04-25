
#ifdef API_GRAPHICS_D3D11

// Primary Include
#include "RHI/CommandList.h"

// Engine Include
#include "RHI/Device.h"
#include "RHI/PipelineState.h"
#include "RHI/Texture2D.h"
#include "RHI/VertexBuffer.h"
#include "RHI/IndexBuffer.h"
#include "RHI/ConstantBuffer.h"


namespace Fluent
{
	CommandList::CommandList(const std::shared_ptr<Device>& device) noexcept
	{
		Assert(device && device->IsInitialized());

		mDeviceContext = device->GetDeviceContext();
		
		const HRESULT result = device->GetDevice()->CreateDeferredContext(0, &mDeferredContext);
		if (SUCCEEDED(result))
		{
			mbIsInitialized = true;
		}
	}

	void CommandList::SetPipelineState(const PipelineState* pipelineState)
	{
		Assert(pipelineState != nullptr);
		
		// Bind vertex shader
		if (pipelineState->mVertexShader != nullptr)
		{
			mDeferredContext->VSSetShader(pipelineState->mVertexShader, nullptr, 0);
		}

		// Bind input layout
		if (pipelineState->mInputLayout != nullptr)
		{
			mDeferredContext->IASetInputLayout(pipelineState->mInputLayout);
		}

		// Bind pixel shader
		if (pipelineState->mPixelShader != nullptr)
		{
			mDeferredContext->PSSetShader(pipelineState->mPixelShader, nullptr, 0);
		}

		// Bind viewport
		if (pipelineState->mViewport.IsDefined())
		{
			SetViewport(pipelineState->mViewport);
		}

		// Bind depth-stencil state
		if (pipelineState->mDepthStencilState != nullptr)
		{
			mDeferredContext->OMSetDepthStencilState(pipelineState->mDepthStencilState, 1);
		}

		// Bind rasterizer state
		if (pipelineState->mRasterizerState != nullptr)
		{
			mDeferredContext->RSSetState(pipelineState->mRasterizerState);
		}

		// Bind primitive topology
		if (pipelineState->mPrimitiveTopology != EPrimitiveTopology::Unknown)
		{
			mDeferredContext->IASetPrimitiveTopology(ToD3D11Topology(pipelineState->mPrimitiveTopology));
		}

		// Bind render target
		if (!pipelineState->mRenderTargetTextures.empty())
		{
			const u32 renderTargetNum = static_cast<u32>(pipelineState->mRenderTargetTextures.size());
			std::vector<ID3D11RenderTargetView*> arrayRTV;
			arrayRTV.reserve(renderTargetNum);

			for (const Texture2D* tex : pipelineState->mRenderTargetTextures)
			{
				arrayRTV.emplace_back(tex->GetRenderTargetView());
			}

			ID3D11DepthStencilView* tempDSV = pipelineState->mDepthStencilTexture->GetDepthStencilView();
			mDeferredContext->OMSetRenderTargets(renderTargetNum, arrayRTV.data(), tempDSV);
		}
	}

	void CommandList::Clear(const PipelineState* pipelineState)
	{
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

	void CommandList::SetScissorRectangle(const Rectangle& rectangle) const
	{
		D3D11_RECT scissorRect = {
			static_cast<u32>(rectangle.MinX), static_cast<u32>(rectangle.MinY),
			static_cast<u32>(rectangle.MaxX), static_cast<u32>(rectangle.MaxY) };

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
		d3dViewport.TopLeftX = viewport.mX;
		d3dViewport.TopLeftY = viewport.mY;
		d3dViewport.Width = viewport.mWidth;
		d3dViewport.Height = viewport.mHeight;
		d3dViewport.MinDepth = viewport.mNear;
		d3dViewport.MaxDepth = viewport.mFar;
		
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
