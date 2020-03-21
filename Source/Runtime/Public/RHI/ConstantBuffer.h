#pragma once

// External Include
#include <memory>

// Engine Include
#include "D3D11/D3DConstantBuffer.h"
#include "Core/Core.h"


namespace Fluent
{
#ifdef API_GRAPHICS_D3D11
	using BufferCommon = D3DBufferCommon;
#endif

	
	class ConstantBuffer :
#ifdef API_GRAPHICS_D3D11
		public D3DConstantBuffer
#endif
	{
	public:

		explicit ConstantBuffer(const std::shared_ptr<Device>& device) noexcept;
		virtual ~ConstantBuffer() noexcept;

		template<typename T>
		bool CreateBuffer();

		[[nodiscard]]
		void* Map() const;
		void Unmap() const;

	private:
		
		bool CreateBufferInternal(uint32 stride);

	private:

		std::shared_ptr<Device> mDevice;

	};

	template <typename T>
	bool ConstantBuffer::CreateBuffer()
	{
		return CreateBufferInternal(static_cast<uint32>(sizeof(T)));
	}
}
