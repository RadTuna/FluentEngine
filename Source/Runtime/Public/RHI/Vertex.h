#pragma once

// Engine Include
#include "Math/Vector4.h"
#include "Math/Vector3.h"
#include "Math/Vector2.h"


namespace Fluent
{

	struct VertexPos
	{
		Vector4 Position;
	};

	struct VertexPosTex
	{
		Vector4 Position;
		Vector2 TexCoord;
	};

	enum class VertexType
	{
		Unknown,
		Pos,
		PosTex
	};

	template<typename T>
	VertexType VertexTypeToEnum() { return VertexType::Unknown; }

	template<> inline VertexType VertexTypeToEnum<VertexPos>() { return VertexType::Pos; }
	template<> inline VertexType VertexTypeToEnum<VertexPosTex>() { return VertexType::PosTex; }
	
}
