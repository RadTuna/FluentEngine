#pragma once

// Engine Include
#include "Core/Core.h"


namespace Fluent
{

	// ========== Renderer enumerate declaration ==========

	constexpr u32 RenderTargetTypesNum = 5;
	namespace ERenderTargetType
	{
		enum Enum : u32
		{
			Albedo = 0,
			Diffuse = 1,
			Specular = 2,
			Normal = 3,
			Depth = 4
		};
	}

	constexpr u32 RenderShaderTypesNum = 2;
	namespace ERenderShaderType
	{
		enum Enum : u32
		{
			VS_Common = 0,
			PS_Common = 1
		};
	}

	constexpr u32 DepthStencilStateTypesNum = 3;
	namespace EDepthStencilStateType
	{
		enum Enum : u32
		{
			Enable_Write = 0,
			Enable_NoWrite = 1,
			Disable = 2
		};
	}

	constexpr u32 ConstantBufferTypesNum = 3;
	namespace EConstantBufferType
	{
		enum Enum : u32
		{
			FrameBuffer = 0,
			UberBuffer = 1,
			LightBuffer = 2
		};
	}

	constexpr u32 RasterizerStateTypesNum = 7;
	namespace ERasterizerStateType
	{
		enum Enum : u32
		{
			CullBack_Solid = 0,
			CullBack_Solid_NoClip = 1,
			CullFront_Solid = 2,
			CullNone_Solid = 3,
			CullBack_WireFrame = 4,
			CullFront_WireFrame = 5,
			CullNone_WireFrame = 6
		};
	}

}
