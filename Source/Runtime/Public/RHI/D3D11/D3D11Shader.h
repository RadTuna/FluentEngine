#pragma once

#ifdef API_GRAPHICS_D3D11

// Engine Include
#include "D3D11Definition.h"


namespace Fluent
{
	
	class D3D11Shader
	{
	public:

		explicit D3D11Shader() = default;
		virtual ~D3D11Shader() = default;

		
		[[nodiscard]]
		ID3D11VertexShader* GetVertexShader() const { return mVertexShader; }

		[[nodiscard]]
		ID3D11PixelShader* GetPixelShader() const { return mPixelShader; }

		[[nodiscard]]
		ID3D11ComputeShader* GetComputeShader() const { return mComputeShader; }

		[[nodiscard]]
		ID3D11InputLayout* GetInputLayout() const { return mInputLayout; }
		
	protected:

		ID3D11Device* mDevice = nullptr;
		
		ID3D11VertexShader* mVertexShader = nullptr;
		ID3D11InputLayout* mInputLayout = nullptr;
		ID3D11PixelShader* mPixelShader = nullptr;
		ID3D11ComputeShader* mComputeShader = nullptr;

	};
	
}

#endif
