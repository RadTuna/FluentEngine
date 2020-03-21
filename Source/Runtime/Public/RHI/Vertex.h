#pragma once

// Engine Include
#include "D3D11/D3DVertex.h"
#include "Core/Core.h"


namespace Fluent
{

#ifdef API_GRAPHICS_D3D11
	using VertexPos = D3DVertexPos;
	using VertexPosTex = D3DVertexPosTex;
#endif

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
