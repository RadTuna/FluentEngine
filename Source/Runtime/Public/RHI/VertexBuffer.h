#pragma once

// External Include
#include <memory>
#include <vector>

// Engine Include
#include "D3D11/D3D11VertexBuffer.h"
#include "Core/Core.h"


namespace Fluent
{
	
	class VertexBuffer final :
#ifdef API_GRAPHICS_D3D11
		public D3D11VertexBuffer
#endif
	{
	public:

		explicit VertexBuffer(const std::shared_ptr<Device>& device) noexcept;
		virtual ~VertexBuffer() noexcept;


		template<typename T>
		bool CreateBuffer(const std::vector<T>& vertices);

		template<typename T>
		bool CreateBuffer(const T* vertices, u32 vertexCount);

		[[nodiscard]]
		void* Map() const;
		void Unmap() const;

		[[nodiscard]]
		u32 GetStride() const { return mStride; }

		[[nodiscard]]
		u32 GetVertexCount() const { return mVertexCount; }

		[[nodiscard]]
		u32 GetSize() const { return mSize; }

	private:
		
		bool CreateBufferInternal(const void* vertices);
		
	private:

		u32 mStride = 0;
		u32 mVertexCount = 0;
		u32 mSize = 0;
		
	};

	template <typename T>
	bool VertexBuffer::CreateBuffer(const std::vector<T>& vertices)
	{
		mStride = static_cast<u32>(sizeof(T));
		mVertexCount = static_cast<u32>(vertices.size());
		mSize = mStride * mVertexCount;

		return CreateBufferInternal(vertices.data());
	}

	template <typename T>
	bool VertexBuffer::CreateBuffer(const T* vertices, u32 vertexCount)
	{
		mStride = static_cast<u32>(sizeof(T));
		mVertexCount = vertexCount;
		mSize = mStride * mVertexCount;

		return CreateBufferInternal(vertices);
	}
}
