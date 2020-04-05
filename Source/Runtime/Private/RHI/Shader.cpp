
#include "RHI/Shader.h"

namespace Fluent
{

	const i8* Shader::GetEntryPoint() const
	{
		static const i8* vertexEntry = "mainVS";
		static const i8* pixelEntry = "mainPS";
		static const i8* computeEntry = "mainCS";

		switch (mShaderType)
		{
			case EShaderType::Vertex:
			{
				return vertexEntry;
			}
			case EShaderType::Pixel:
			{
				return pixelEntry;
			}
			case EShaderType::Compute:
			{
				return computeEntry;
			}
			default:
			{
				Assert(false);
				return nullptr;
			}
		}
	}

	const i8* Shader::GetTargetProfile() const
	{
#ifdef API_GRAPHICS_D3D11
		static const i8* targetVS = "vs_5_0";
		static const i8* targetPS = "ps_5_0";
		static const i8* targetCS = "cs_5_0";
#endif

		switch (mShaderType)
		{
		case EShaderType::Vertex:
		{
			return targetVS;
		}
		case EShaderType::Pixel:
		{
			return targetPS;
		}
		case EShaderType::Compute:
		{
			return targetCS;
		}
		default:
		{
			Assert(false);
			return nullptr;
		}
		}
	}

	
}
