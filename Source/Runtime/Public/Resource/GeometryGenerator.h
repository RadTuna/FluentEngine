#pragma once

// Engine Include
#include "Core/Core.h"
#include "Resource/Mesh.h"


namespace Fluent
{

	class GeometryGenerator final
	{
	public:

		GeometryGenerator() = delete;
		~GeometryGenerator() = delete;
		
		static Mesh CreateBox(f32 width, f32 height, f32 depth);
		static Mesh CreateQuad(f32 x, f32 y, f32 width, f32 height, f32 depth);
		
	};
	
}
