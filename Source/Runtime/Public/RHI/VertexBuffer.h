#pragma once

// External Include
#include <memory>
#include <vector>

// Engine Include
#include "D3D11/D3DVertexBuffer.h"
#include "Core/Core.h"


namespace Fluent
{
	
	class VertexBuffer final :
#ifdef API_GRAPHICS_D3D11
		public D3DVertexBuffer
#endif
	{
	public:

		explicit VertexBuffer(const std::shared_ptr<Device>& device) noexcept;
		virtual ~VertexBuffer() noexcept;


		template<typename T>
		bool CreateBuffer(const std::vector<T>& vertices);

		template<typename T>
		bool CreateBuffer(const T* vertices, uint32 vertexCount);

		[[nodiscard]]
		void* Map() const;
		void Unmap() const;

	private:
		
		bool CreateBufferInternal(const void* vertices);
		
	private:

		std::shared_ptr<Device> mDevice;
		uint32 mStride = 0;
		uint32 mVertexCount = 0;
		uint32 mSize = 0;
		
	};

	template <typename T>
	bool VertexBuffer::CreateBuffer(const std::vector<T>& vertices)
	{
		mStride = static_cast<uint32>(sizeof(T));
		mVertexCount = static_cast<uint32>(vertices.size());
		mSize = mStride * mVertexCount;

		return CreateBufferInternal(vertices.data());
	}

	template <typename T>
	bool VertexBuffer::CreateBuffer(const T* vertices, uint32 vertexCount)
	{
		mStride = static_cast<uint32>(sizeof(T));
		mVertexCount = vertexCount;
		mSize = mStride * mVertexCount;

		return CreateBufferInternal(vertices);
	}
}
