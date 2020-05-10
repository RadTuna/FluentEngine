
#ifdef API_GRAPHICS_D3D11

// Primary Include
#include "RHI/ConstantBuffer.h"

// Engine Include
#include "RHI/Device.h"

namespace Fluent
{

	ConstantBuffer::ConstantBuffer(const std::shared_ptr<Device>& device) noexcept
	{
		Assert(device && device->IsInitialized());
		mDevice = device->GetDevice();
		mDeviceContext = device->GetDeviceContext();
	}

	ConstantBuffer::~ConstantBuffer() noexcept
	{
		D3D11Release(mConstantBuffer);
	}

	bool ConstantBuffer::CreateBufferInternal()
	{
		D3D11Release(mConstantBuffer);
		
		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.ByteWidth = mSize;
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bufferDesc.MiscFlags = 0;
		//bufferDesc.StructureByteStride = 0;

		const HRESULT result = mDevice->CreateBuffer(&bufferDesc, nullptr, &mConstantBuffer);
		if (FAILED(result))
		{
			return false;
		}

		return true;
	}

	void* ConstantBuffer::Map() const
	{
		D3D11_MAPPED_SUBRESOURCE mappedSubResource = {};
		const HRESULT result = mDeviceContext->Map(mConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubResource);
		if (FAILED(result))
		{
			return nullptr;
		}

		return mappedSubResource.pData;
	}

	void ConstantBuffer::Unmap() const
	{
		mDeviceContext->Unmap(mConstantBuffer, 0);
	}

	
}

#endif
