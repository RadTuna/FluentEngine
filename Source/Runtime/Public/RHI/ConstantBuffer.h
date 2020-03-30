#pragma once

// External Include
#include <memory>

// Engine Include
#include "D3D11/D3D11ConstantBuffer.h"
#include "Core/Core.h"


namespace Fluent
{
	
	class ConstantBuffer :
#ifdef API_GRAPHICS_D3D11
		public D3D11ConstantBuffer
#endif
	{
	public:

		explicit ConstantBuffer(const std::shared_ptr<Device>& device) noexcept;
		virtual ~ConstantBuffer() noexcept;

		template<typename T>
		bool CreateBuffer(uint32 instanceNum = 1);

		[[nodiscard]]
		void* Map() const;
		void Unmap() const;

	private:
		
		bool CreateBufferInternal();

	private:

		std::shared_ptr<Device> mDevice;
		uint32 mStride = 0;
		uint32 mInstanceCount = 1;
		uint32 mSize = 0;

	};

	template <typename T>
	bool ConstantBuffer::CreateBuffer(uint32 instanceNum)
	{
		mStride = static_cast<uint32>(sizeof(T));
		mInstanceCount = instanceNum;
		mSize = mStride * mInstanceCount;
		
		return CreateBufferInternal();
	}
}
