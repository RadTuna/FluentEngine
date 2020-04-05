#pragma once

// External Include
#include <memory>
#include <vector>

// Engine Include
#include "Core/Core.h"
#include "RHI/RHIDefinition.h"


namespace Fluent
{

	class Texture
	{
	public:

		explicit Texture(const std::shared_ptr<Device>& device) noexcept : mDevice(device) {}
		virtual ~Texture() = default;


		// Getters
		
		[[nodiscard]]
		u32 GetBitPerPixel() const { return mBpp; }
		[[nodiscard]]
		u32 GetBitPerColor() const { return mBpc; }
		[[nodiscard]]
		u32 GetWidth() const { return mWidth; }
		[[nodiscard]]
		u32 GetHeight() const { return mHeight; }
		[[nodiscard]]
		u32 GetChannels() const { return mChannels; }
		[[nodiscard]]
		u32 GetTextureArraySize() const { return mTextureArraySize; }
		[[nodiscard]]
		u32 GetMipLevel() const { return mMipLevel; }
		[[nodiscard]]
		bool IsTransparent() const { return mbIsTransparent; }

		// Other functions

		[[nodiscard]]
		u32 GetChannelCountFromFormat(EPixelFormat format) const;
		
	protected:

		virtual bool CreateTexture(const std::vector<std::vector<u8>>& data, u32 arraySize) { return false; }
		virtual bool CreateEmptyTexture() { return false; }

	protected:

		u32 mBpp = 0;
		u32 mBpc = 0;
		u32 mWidth = 0;
		u32 mHeight = 0;
		u32 mChannels = 4;
		u32 mTextureArraySize = 1;
		u32 mMipLevel = 1;
		EPixelFormat mFormat = EPixelFormat::Unknown;
		bool mbIsTransparent = true;
		u32 mViewFlags = 0; // Equal to ETextureViewFlags::Unknown

		std::shared_ptr<Device> mDevice;
		
	};
	
}
