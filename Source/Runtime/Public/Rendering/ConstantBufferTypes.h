#pragma once

#include "Core/TypeDefinition.h"
#include "Math/Matrix4x4.h"

namespace Fluent
{

	struct BufferFrame
	{
		Matrix4x4 WorldMatrix;
		Matrix4x4 ViewMatrix;
		Matrix4x4 ProjectionMatrix;

		f32 CameraNear;
		f32 CameraFar;

		f32 padding[2];
	};

}
