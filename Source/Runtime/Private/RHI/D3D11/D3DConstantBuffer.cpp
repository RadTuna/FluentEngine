
#ifdef API_GRAPHICS_D3D11

// Engine Include
#include "RHI/ConstantBuffer.h"
#include "RHI/Device.h"

namespace Fluent
{

	ConstantBuffer::ConstantBuffer(const std::shared_ptr<Device>& device) noexcept
	{
		Assert(device && device->IsInitialized());
		mDevice = device;
	}

	ConstantBuffer::~ConstantBuffer() noexcept
	{
		
	}

	bool ConstantBuffer::CreateBufferInternal(uint32 stride)
	{	
		if (!mDevice || !mDevice->GetDevice())
		{
			return false;
		}
		
		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.ByteWidth = stride;
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bufferDesc.MiscFlags = 0;
		bufferDesc.StructureByteStride = 0;

		const HRESULT result = mDevice->GetDevice()->CreateBuffer(&bufferDesc, nullptr, &mBuffer);
		if (FAILED(result))
		{
			return false;
		}

		return true;
	}

	void* ConstantBuffer::Map() const
	{
		D3D11_MAPPED_SUBRESOURCE mappedSubResource = {};
		const HRESULT result = mDevice->GetDeviceContext()->Map(mBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubResource);
		if (FAILED(result))
		{
			return nullptr;
		}

		return mappedSubResource.pData;
	}

	void ConstantBuffer::Unmap() const
	{
		mDevice->GetDeviceContext()->Unmap(mBuffer, 0);
	}

	
}

#endif
