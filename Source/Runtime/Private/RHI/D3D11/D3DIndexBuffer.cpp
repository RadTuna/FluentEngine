
#ifdef API_GRAPHICS_D3D11

// Primary Include
#include "RHI/IndexBuffer.h"

// Engine Include
#include "RHI/Device.h"


namespace Fluent
{

	IndexBuffer::IndexBuffer(const std::shared_ptr<Device>& device) noexcept
	{
		Assert(device && device->IsInitialized());

		mDevice = device;
	}

	IndexBuffer::~IndexBuffer() noexcept
	{
		D3DRelease(mIndexBuffer);
	}

	bool IndexBuffer::CreateBufferInternal(const void* indices)
	{
		D3DRelease(mIndexBuffer);

		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.ByteWidth = static_cast<UINT>(mSize);
		bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
		bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
		bufferDesc.MiscFlags = 0;
		bufferDesc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA subResource = {};
		subResource.pSysMem = indices;
		subResource.SysMemPitch = 0;
		subResource.SysMemSlicePitch = 0;

		const HRESULT result = mDevice->GetDevice()->CreateBuffer(&bufferDesc, &subResource, &mIndexBuffer);
		if (SUCCEEDED(result))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	
}

#endif

