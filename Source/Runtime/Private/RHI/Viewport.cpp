
// Primary Include
#include "RHI/Viewport.h"


namespace Fluent
{

	Viewport::Viewport(f32 locX, f32 locY, f32 width, f32 height, f32 near, f32 far)
	{
		mX = locX; mY = locY;
		mWidth = width; mHeight = height;
		mNear = near; mFar = far;
	}

	bool Viewport::IsEqual(const Viewport& other) const
	{
		return
			mX == other.mX && mY == other.mY &&
			mWidth == other.mWidth && mHeight == other.mHeight &&
			mNear == other.mNear && mHeight && other.mHeight;
	}

	bool Viewport::IsDefined() const
	{
		return
			mX != 0.0f || mY != 0.0f ||
			mWidth != 0.0f || mHeight != 0.0f ||
			mNear != 0.0f || mFar != 0.0f;
	}
	
}
