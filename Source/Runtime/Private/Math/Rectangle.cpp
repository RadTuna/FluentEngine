
// Primary Include
#include "Math/Rectangle.h"


namespace Fluent
{

	Rectangle::Rectangle(f32 minX, f32 minY, f32 maxX, f32 maxY) noexcept
	{
		MinX = minX; MinY = minY;
		MaxX = maxX; MaxY = maxY;
	}

	bool Rectangle::operator==(const Rectangle& other)
	{
		return
			MinX == other.MinX && MinY == other.MinY &&
			MaxX == other.MaxX && MaxY == other.MaxY;
	}

	bool Rectangle::operator!=(const Rectangle& other)
	{
		return
			MinX != other.MinX || MinY != other.MinY ||
			MaxX != other.MaxX || MaxY != other.MaxY;
	}

	f32 Rectangle::GetArea() const
	{
		const f32 width = GetWidth();
		const f32 height = GetHeight();

		return width * height;
	}

	f32 Rectangle::GetHeight() const
	{
		return MaxY - MinY;
	}

	f32 Rectangle::GetWidth() const
	{
		return MaxX - MinX;
	}
	
}
