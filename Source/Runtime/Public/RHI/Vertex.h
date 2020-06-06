#pragma once

// External Include
#include <string>

// Engine Include
#include "RHI/RHIDefinition.h"
#include "Math/Vector4.h"
#include "Math/Vector3.h"
#include "Math/Vector2.h"


namespace Fluent
{
	
	struct InputLayout
	{
		std::string SemanticName;
		u32 SemanticIndex;
		EPixelFormat Format;
		u32 InputSlot;
		u32 ByteOffset;
		u32 InstanceStepRate;
	};
	constexpr u32 VertexTypesNum = 3;
	constexpr u32 InputLayoutMapsNum[VertexTypesNum] = { 1, 2, 5 };

	
	struct VertexPos
	{
		Vector4 Position;
	};
	static const InputLayout VertexPosInputLayout[InputLayoutMapsNum[0]] =
	{
		{ "POSITION", 0, EPixelFormat::R32G32B32A32_Float, 0, offsetof(VertexPos, Position), 0 }
	};

	
	struct VertexPosTex
	{
		Vector4 Position;
		Vector2 TexCoord;
	};
	static const InputLayout VertexPosTexInputLayout[InputLayoutMapsNum[1]] =
	{
		{ "POSITION", 0, EPixelFormat::R32G32B32A32_Float, 0, offsetof(VertexPosTex, Position), 0 },
		{ "TEXCOORD", 0, EPixelFormat::R32G32_Float, 0, offsetof(VertexPosTex, TexCoord), 0 }
	};


	struct VertexPosTexNorTan
	{
		Vector4 Position;
		Vector2 TexCoord;
		Vector3 Normal;
		Vector3 Tangent;
		Vector3 BiTangent;
	};
	static const InputLayout VertexPosTexNorTanInputLayout[InputLayoutMapsNum[2]] =
	{
		{ "POSITION", 0, EPixelFormat::R32G32B32A32_Float, 0, offsetof(VertexPosTexNorTan, Position), 0 },
		{ "TEXCOORD", 0, EPixelFormat::R32G32_Float, 0, offsetof(VertexPosTexNorTan, TexCoord), 0 },
		{ "NORMAL", 0, EPixelFormat::R32G32B32_Float, 0, offsetof(VertexPosTexNorTan, Normal), 0 },
		{ "TANGENT", 0, EPixelFormat::R32G32B32_Float, 0, offsetof(VertexPosTexNorTan, Tangent), 0 },
		{ "TANGENT", 1, EPixelFormat::R32G32B32_Float, 0, offsetof(VertexPosTexNorTan, BiTangent), 0 }
	};

	
	static const InputLayout* InputLayoutMap[] =
	{
		VertexPosInputLayout,
		VertexPosTexInputLayout
	};

	enum class EVertexType : u32
	{
		Unknown = static_cast<u32>(-1),
		Pos = 0,
		PosTex = 1
	};

	template<typename T>
	EVertexType VertexTypeToEnum() { return EVertexType::Unknown; }

	template<> inline EVertexType VertexTypeToEnum<VertexPos>() { return EVertexType::Pos; }
	template<> inline EVertexType VertexTypeToEnum<VertexPosTex>() { return EVertexType::PosTex; }
	
}
