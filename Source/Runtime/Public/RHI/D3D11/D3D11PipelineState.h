#pragma once

#ifdef API_GRAPHICS_D3D11

// Engine Include
#include "D3D11Definition.h"


namespace Fluent
{

	class D3D11PipelineState
	{
	public:

		explicit D3D11PipelineState() = default;
		virtual ~D3D11PipelineState() = default;
		
	public:

		// Store objects
		ID3D11VertexShader* mVertexShader = nullptr;
		ID3D11PixelShader* mPixelShader = nullptr;
		ID3D11RasterizerState* mRasterizerState = nullptr;
		ID3D11DepthStencilState* mDepthStencilState = nullptr;
		ID3D11InputLayout* mInputLayout = nullptr;

	};

}

#endif
