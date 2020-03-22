#pragma once

// External Include
#include <memory>
#include <vector>

// Engine Include
#include "D3D11/D3DIndexBuffer.h"
#include "Core/Core.h"


namespace Fluent
{
	
	class IndexBuffer final :
#ifdef API_GRAPHICS_D3D11
		public D3DIndexBuffer
#endif
	{
	public:

		explicit IndexBuffer(const std::shared_ptr<Device>& device) noexcept;
		virtual ~IndexBuffer() noexcept;

		
		template<typename T>
		bool CreateBuffer(const std::vector<T>& indices);

		template<typename T>
		bool CreateBuffer(const T* indices, uint32 indexCount);

		[[nodiscard]]
		void* Map() const;
		void Unmap() const;
		
	private:

		bool CreateBufferInternal(const void* indices);
		
	private:

		std::shared_ptr<Device> mDevice;
		uint32 mStride = 0;
		uint32 mIndexCount = 0;
		uint32 mSize = 0;
		
	};

	template <typename T>
	bool IndexBuffer::CreateBuffer(const std::vector<T>& indices)
	{
		mStride = static_cast<uint32>(sizeof(T));
		mIndexCount = static_cast<uint32>(indices.size());
		mSize = mStride * mIndexCount;

		return CreateBufferInternal(indices.data());
	}

	template <typename T>
	bool IndexBuffer::CreateBuffer(const T* indices, uint32 indexCount)
	{
		mStride = static_cast<uint32>(sizeof(T));
		mIndexCount = indexCount;
		mSize = mStride * mIndexCount;

		return CreateBufferInternal(indices);
	}
	
}
