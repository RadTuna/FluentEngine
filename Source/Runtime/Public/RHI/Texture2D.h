#pragma once

// Engine Include
#include "Texture.h"
#include "D3D11/D3D11Texture2D.h"


namespace Fluent
{

	class Texture2D final : public Texture,
#ifdef API_GRAPHICS_D3D11
		public D3D11Texture2D
#endif
	{
	public:

		// Create texture with data
		explicit Texture2D(const std::shared_ptr<Device>& device,
			u32 width, u32 height, EPixelFormat format,
			const std::vector<std::vector<u8>>& data) noexcept;

		// Create texture without data
		explicit Texture2D(const std::shared_ptr<Device>& device,
			u32 width, u32 height, EPixelFormat format) noexcept;

		virtual ~Texture2D() noexcept;

		
		bool CreateTexture(const std::vector<std::vector<u8>>& data, u32 arraySize) override;
		bool CreateEmptyTexture() override;

	private:
		
	};
	
}
