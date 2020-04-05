#pragma once

// External Include
#include <string>

// Engine Include
#include "Core/Core.h"
#include "Math/Matrix4x4.h"

namespace Fluent
{

	// ========== Forward declaration ==========
	
	class CommandList;
	class ConstantBuffer;
	class DepthStencilState;
	class Device;
	class IndexBuffer;
	class RasterizerState;
	class Shader;
	class RasterizerState;
	class SwapChain;
	class Texture;
	class Texture2D;
	class Texture3D;
	class Vertex;
	class VertexBuffer;


	// ========== Render structure declaration ==========
	
	struct PhysicalDeviceData
	{
		PhysicalDeviceData() = default;
		PhysicalDeviceData(const std::string& name, u32 mem) : DeviceName(name), Memory(mem) {}

		std::string DeviceName = "Unknown";
		u32 Memory = 0;
	};

	struct DisplayMode
	{
		DisplayMode() = default;
		DisplayMode(u32 inWidth, u32 inHeight, u32 inNumerator, u32 inDenominator, double inRefresh)
			: Width(inWidth), Height(inHeight), Numerator(inNumerator), Denominator(inDenominator), RefreshRate(inRefresh) {}

		u32 Width = 0;
		u32 Height = 0;
		u32 Numerator = 0;
		u32 Denominator = 0;
		double RefreshRate = 0.0;
	};

	struct BufferCommon
	{
		Matrix4x4 WorldMatrix;
		Matrix4x4 ViewMatrix;
		Matrix4x4 ProjectionMatrix;
	};


	// ========== Render enumerate declaration ==========
	
	namespace ETextureViewFlags
	{
		enum ETextureViewFlags : u32
		{
			Unknown = 0,
			RenderTarget = 1,
			DepthStencil = 1 << 1,
			ShaderSampled = 1 << 2
		};
	}
	
	enum class ERenderCullMode
	{
		Unknown,
		None,
		Front,
		Back
	};

	enum class ERenderFillMode
	{
		Unknown,
		Solid,
		WireFrame
	};

	enum class EPixelFormat : u32
	{
		Unknown = 0,
		
		// R
		R8_Unorm,
		R16_Uint,
		R16_Float,
		R32_Uint,
		R32_Float,
		D32_Float,
		R32_Float_Typeless,
		
		// RG
		R8G8_Unorm,
		R16G16_Float,
		R32G32_Float,
		
		// RGB
		R32G32B32_Float,
		
		// RGBA
		R8G8B8A8_Unorm,
		R16G16B16A16_Float,
		R32G32B32A32_Float,
	};
	
}
