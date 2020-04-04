#pragma once

// Engine Include
#include "Core/Core.h"


namespace Fluent
{

	// ========== Renderer enumerate declaration ==========

	constexpr uint32 RenderTargetTypesNum = 1;
	namespace ERenderTargetType
	{
		enum ERenderTargetType : uint32
		{
			Albedo = 0
		};
	}

	constexpr uint32 RenderShaderTypesNum = 2;
	namespace ERenderShaderType
	{
		enum ERenderShaderType : uint32
		{
			VS_Common = 0,
			PS_Common = 1
		};
	}

	constexpr uint32 DepthStencilStateTypesNum = 3;
	namespace EDepthStencilStateType
	{
		enum EDepthStencilStateType : uint32
		{
			Enable_Write = 0,
			Enable_NoWrite = 1,
			Disable = 2
		};
	}

	constexpr uint32 ConstantBufferTypesNum = 3;
	namespace EConstantBufferType
	{
		enum ERenderBufferType : uint32
		{
			FrameBuffer = 0,
			UberBuffer = 1,
			LightBuffer = 2
		};
	}

	constexpr uint32 RasterizerStateTypesNum = 7;
	namespace ERasterizerStateType
	{
		enum ERasterizerStateType : uint32
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
