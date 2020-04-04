
// Primary Include
#include "RHI/Texture.h"


namespace Fluent
{

	uint32 Texture::GetChannelCountFromFormat(EPixelFormat format) const
	{
		switch (format)
		{
		case EPixelFormat::Unknown:
			return 0;
		case EPixelFormat::R8_Unorm:
		case EPixelFormat::R16_Float:
		case EPixelFormat::R32_Uint:
		case EPixelFormat::R32_Float:
		case EPixelFormat::D32_Float:
		case EPixelFormat::R32_Float_Typeless:
			return 1;

		case EPixelFormat::R8G8_Unorm:
		case EPixelFormat::R16G16_Float:
		case EPixelFormat::R32G32_Float:
			return 2;

		case EPixelFormat::R32G32B32_Float:
			return 3;

		case EPixelFormat::R8G8B8A8_Unorm:
		case EPixelFormat::R16G16B16A16_Float:
		case EPixelFormat::R32G32B32A32_Float:
			return 4;

		default:
			Assert(false);
			return INDEX_NONE;
		}
	}

	
}
