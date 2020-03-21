
#include "RHI/Shader.h"

namespace Fluent
{

	const char* Shader::GetEntryPoint() const
	{
		static const char* vertexEntry = "mainVS";
		static const char* pixelEntry = "mainPS";
		static const char* computeEntry = "mainCS";

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

	const char* Shader::GetTargetProfile() const
	{
#ifdef API_GRAPHICS_D3D11
		static const char* targetVS = "vs_5_0";
		static const char* targetPS = "ps_5_0";
		static const char* targetCS = "cs_5_0";
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
