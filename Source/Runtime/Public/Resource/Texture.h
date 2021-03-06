#pragma once

// External Include
#include <memory>
#include <vector>

// Engine Include
#include "Core/Core.h"
#include "RHI/RHIDefinition.h"
#include "Resource/IResource.h"


namespace Fluent
{
	
	class Texture : public IResource
	{
	public:
		explicit Texture() noexcept;
		virtual ~Texture() = default;

		// IResource interface implementation
		bool SaveToFile(const std::string& savePath) override;
		bool LoadFromFile(const std::string& loadPath) override;

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
		virtual void CreateTexture(const std::vector<std::vector<u8>>& data, u32 arraySize) = 0;
		virtual void CreateEmptyTexture() = 0;

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
		u32 mViewFlags = ETextureViewFlags::Unknown; // Equal to ETextureViewFlags::Unknown
		
	};
	
}
