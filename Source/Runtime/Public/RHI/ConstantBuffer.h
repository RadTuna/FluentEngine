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
		bool CreateBuffer(u32 instanceNum = 1);

		[[nodiscard]]
		void* Map() const;
		void Unmap() const;

	private:
		
		bool CreateBufferInternal();

	private:

		u32 mStride = 0;
		u32 mInstanceCount = 1;
		u32 mSize = 0;

	};

	template <typename T>
	bool ConstantBuffer::CreateBuffer(u32 instanceNum)
	{
		mStride = static_cast<u32>(sizeof(T));
		mInstanceCount = instanceNum;
		mSize = mStride * mInstanceCount;
		
		return CreateBufferInternal();
	}
}
