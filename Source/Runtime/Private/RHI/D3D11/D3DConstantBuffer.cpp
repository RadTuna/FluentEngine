
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
		D3DRelease(mConstantBuffer);
	}

	bool ConstantBuffer::CreateBufferInternal()
	{
		D3DRelease(mConstantBuffer);
		
		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.ByteWidth = static_cast<UINT>(mSize);
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bufferDesc.MiscFlags = 0;
		bufferDesc.StructureByteStride = 0;

		const HRESULT result = mDevice->GetDevice()->CreateBuffer(&bufferDesc, nullptr, &mConstantBuffer);
		if (FAILED(result))
		{
			return false;
		}

		return true;
	}

	void* ConstantBuffer::Map() const
	{
		D3D11_MAPPED_SUBRESOURCE mappedSubResource = {};
		const HRESULT result = mDevice->GetDeviceContext()->Map(mConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubResource);
		if (FAILED(result))
		{
			return nullptr;
		}

		return mappedSubResource.pData;
	}

	void ConstantBuffer::Unmap() const
	{
		mDevice->GetDeviceContext()->Unmap(mConstantBuffer, 0);
	}

	
}

#endif
