#pragma once

// Engine Include
#include "Core/Core.h"


namespace Fluent
{

	// ========== Renderer enumerate declaration ==========

	constexpr u32 RenderTargetTypesNum = 3;
	namespace ERenderTargetType
	{
		enum Enum : u32
		{
			Albedo = 0, // R8G8B8A8 : unlit color
			Material = 1, // R8 : metallic, G8 : roughness, B8A8 : padding
			Normal = 2 // R16G16B16 : normal vector, A16 : padding
		};
	}

	constexpr u32 RenderShaderTypesNum = 2;
	namespace ERenderShaderType
	{
		enum Enum : u32
		{
			VS_Quad = 0,
			PS_Quad = 1
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

	constexpr u32 RasterizerStateTypesNum = 8;
	namespace ERasterizerStateType
	{
		enum Enum : u32
		{
			CullBackSolid = 0,
			CullBackSolidNoClip = 1,
			CullFrontSolid = 2,
			CullNoneSolid = 3,
			CullNoneSolidNoClip = 4,
			CullBackWireFrame = 5,
			CullFrontWireFrame = 6,
			CullNoneWireFrame = 7
		};
	}

	constexpr u32 BlendStateTypesNum = 4;
	namespace EBlendStateType
	{
		enum Enum : u32
		{
			Disable,
			Enable,
			ColorAdd,
			Bloom
		};
	}

	constexpr u32 SamplerTypesNum = 9;
	namespace ESamplerType
	{
		enum Enum : u32
		{
			PointClamp = 0,
			PointWrap,
			BilinearClamp,
			BilinearWrap,
			TrilinearClamp,
			TrilinearWrap,
			AnisotropyClamp,
			AnisotropyWrap,
			CompareDepth,
		};
	}

}
