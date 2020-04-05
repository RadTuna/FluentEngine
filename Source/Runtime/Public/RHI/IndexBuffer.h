#pragma once

// External Include
#include <memory>
#include <vector>

// Engine Include
#include "D3D11/D3D11IndexBuffer.h"
#include "Core/Core.h"


namespace Fluent
{
	
	class IndexBuffer final :
#ifdef API_GRAPHICS_D3D11
		public D3D11IndexBuffer
#endif
	{
	public:

		explicit IndexBuffer(const std::shared_ptr<Device>& device) noexcept;
		virtual ~IndexBuffer() noexcept;

		
		template<typename T>
		bool CreateBuffer(const std::vector<T>& indices);

		template<typename T>
		bool CreateBuffer(const T* indices, u32 indexCount);

		[[nodiscard]]
		void* Map() const;
		void Unmap() const;
		
	private:

		bool CreateBufferInternal(const void* indices);
		
	private:

		std::shared_ptr<Device> mDevice;
		u32 mStride = 0;
		u32 mIndexCount = 0;
		u32 mSize = 0;
		
	};

	template <typename T>
	bool IndexBuffer::CreateBuffer(const std::vector<T>& indices)
	{
		mStride = static_cast<u32>(sizeof(T));
		mIndexCount = static_cast<u32>(indices.size());
		mSize = mStride * mIndexCount;

		return CreateBufferInternal(indices.data());
	}

	template <typename T>
	bool IndexBuffer::CreateBuffer(const T* indices, u32 indexCount)
	{
		mStride = static_cast<u32>(sizeof(T));
		mIndexCount = indexCount;
		mSize = mStride * mIndexCount;

		return CreateBufferInternal(indices);
	}
	
}
