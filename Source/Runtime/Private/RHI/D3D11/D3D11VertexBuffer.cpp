
#ifdef API_GRAPHICS_D3D11

// Primary Include
#include "RHI/VertexBuffer.h"

// Engine Include
#include "RHI/Device.h"


namespace Fluent
{

	VertexBuffer::VertexBuffer(const std::shared_ptr<Device>& device) noexcept
	{
		Assert(device && device->IsInitialized());

		mDevice = device->GetDevice();
		mDeviceContext = device->GetDeviceContext();
	}

	VertexBuffer::~VertexBuffer() noexcept
	{
		D3D11Release(mVertexBuffer);
	}

	bool VertexBuffer::CreateBufferInternal(const void* vertices)
	{
		D3D11Release(mVertexBuffer);

		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.ByteWidth = static_cast<UINT>(mSize);
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.MiscFlags = 0;
		bufferDesc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA subResource = {};
		subResource.pSysMem = vertices;
		subResource.SysMemPitch = 0;
		subResource.SysMemSlicePitch = 0;
		
		const HRESULT result = mDevice->CreateBuffer(&bufferDesc, &subResource, &mVertexBuffer);
		if (SUCCEEDED(result))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void* VertexBuffer::Map() const
	{
		D3D11_MAPPED_SUBRESOURCE mappedSubResource = {};
		const HRESULT result = mDeviceContext->Map(mVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubResource);
		if (FAILED(result))
		{
			return nullptr;
		}

		return mappedSubResource.pData;
	}

	void VertexBuffer::Unmap() const
	{
		mDeviceContext->Unmap(mVertexBuffer, 0);
	}

	
}

#endif
