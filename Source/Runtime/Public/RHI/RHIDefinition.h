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
	class Device;
	class IndexBuffer;
	class InputLayout;
	class PixelShader;
	class RasterizerState;
	class SwapChain;
	class Vertex;
	class VertexBuffer;
	class VertexShader;
	class Viewport;


	// ========== Render structure declaration ==========
	
	struct PhysicalDeviceData
	{
		PhysicalDeviceData() = default;
		PhysicalDeviceData(const std::string& name, uint32 mem) : DeviceName(name), Memory(mem) {}

		std::string DeviceName = "Unknown";
		uint32 Memory = 0;
	};

	struct DisplayMode
	{
		DisplayMode() = default;
		DisplayMode(uint32 inWidth, uint32 inHeight, uint32 inNumerator, uint32 inDenominator, double inRefresh)
			: Width(inWidth), Height(inHeight), Numerator(inNumerator), Denominator(inDenominator), RefreshRate(inRefresh) {}

		uint32 Width = 0;
		uint32 Height = 0;
		uint32 Numerator = 0;
		uint32 Denominator = 0;
		double RefreshRate = 0.0;
	};

	struct BufferCommon
	{
		Matrix4x4 WorldMatrix;
		Matrix4x4 ViewMatrix;
		Matrix4x4 ProjectionMatrix;
	};


	// ========== Render enumerate declaration ==========

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
	
}
