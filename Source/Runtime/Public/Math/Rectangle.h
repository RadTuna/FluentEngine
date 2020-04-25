#pragma once

// Engine Include
#include "Core/TypeDefinition.h"


namespace Fluent
{

	struct Rectangle
	{
	public:

		f32 MinX;
		f32 MinY;
		f32 MaxX;
		f32 MaxY;
		
	public:

		explicit Rectangle(f32 minX, f32 minY, f32 maxX, f32 maxY) noexcept;
		~Rectangle() = default;

		bool operator==(const Rectangle& other);

		bool operator!=(const Rectangle& other);
		
		[[nodiscard]]
		f32 GetArea() const;

		[[nodiscard]]
		f32 GetHeight() const;

		[[nodiscard]]
		f32 GetWidth() const;
		
	};
	
}
