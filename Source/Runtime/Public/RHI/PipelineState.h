#pragma once

#include <vector>

// Engine Include
#include "D3D11/D3D11PipelineState.h"
#include "Core/Core.h"
#include "RHI/Viewport.h"


namespace Fluent
{

	class PipelineState final :
#ifdef API_GRAPHICS_D3D11
		public D3D11PipelineState
#endif
	{
	public:

		explicit PipelineState() = default;
		virtual ~PipelineState() = default;

	public:

		std::vector<Texture2D*> mRenderTargetTextures;
		Texture2D* mDepthStencilTexture = nullptr;
		Viewport mViewport;
		EPrimitiveTopology mPrimitiveTopology;

	};

}
