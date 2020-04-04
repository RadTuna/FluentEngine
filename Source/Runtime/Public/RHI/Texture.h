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
		uint32 GetBitPerPixel() const { return mBpp; }
		[[nodiscard]]
		uint32 GetBitPerColor() const { return mBpc; }
		[[nodiscard]]
		uint32 GetWidth() const { return mWidth; }
		[[nodiscard]]
		uint32 GetHeight() const { return mHeight; }
		[[nodiscard]]
		uint32 GetChannels() const { return mChannels; }
		[[nodiscard]]
		uint32 GetTextureArraySize() const { return mTextureArraySize; }
		[[nodiscard]]
		uint32 GetMipLevel() const { return mMipLevel; }
		[[nodiscard]]
		bool IsTransparent() const { return mbIsTransparent; }

		// Other functions

		[[nodiscard]]
		uint32 GetChannelCountFromFormat(EPixelFormat format) const;
		
	protected:

		virtual bool CreateTexture(const std::vector<std::vector<uint8>>& data, uint32 arraySize) { return false; }
		virtual bool CreateEmptyTexture() { return false; }

	protected:

		uint32 mBpp = 0;
		uint32 mBpc = 0;
		uint32 mWidth = 0;
		uint32 mHeight = 0;
		uint32 mChannels = 4;
		uint32 mTextureArraySize = 1;
		uint32 mMipLevel = 1;
		EPixelFormat mFormat = EPixelFormat::Unknown;
		bool mbIsTransparent = true;
		uint32 mViewFlags = 0; // Equal to ETextureViewFlags::Unknown

		std::shared_ptr<Device> mDevice;
		
	};
	
}
