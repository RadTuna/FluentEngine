#pragma once

// Engine Include
#include "Core/Core.h"


namespace Fluent
{

	class Viewport final
	{
	public:

		explicit Viewport(f32 locX, f32 locY, f32 width, f32 height, f32 near, f32 far);
		~Viewport() = default;

		
		[[nodiscard]]
		bool IsEqual(const Viewport& other) const;

		[[nodiscard]]
		bool IsDefined() const;

	public:

		f32 mX = 0.0f;
		f32 mY = 0.0f;
		f32 mWidth = 0.0f;
		f32 mHeight = 0.0f;
		f32 mNear = 0.0f;
		f32 mFar = 0.0f;

	};

}
