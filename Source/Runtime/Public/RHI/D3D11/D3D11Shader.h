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
		ID3D11VertexShader* GetVertexShader() const { return static_cast<ID3D11VertexShader*>(mShader); }

		[[nodiscard]]
		ID3D11PixelShader* GetPixelShader() const { return static_cast<ID3D11PixelShader*>(mShader); }

		[[nodiscard]]
		ID3D11ComputeShader* GetComputeShader() const { return static_cast<ID3D11ComputeShader*>(mShader); }
		
	protected:

		ID3D11Device* mDevice = nullptr;
		
		void* mShader = nullptr;

	};
	
}

#endif
