#pragma once

// External Include
#include <vector>

// Engine Include
#include "RHI/RHIDefinition.h"

#ifdef API_GRAPHICS_D3D11

namespace Fluent
{
	
	class D3DShader
	{
	public:

		explicit D3DShader() = default;
		virtual ~D3DShader() = default;

		[[nodiscard]]
		ID3D11VertexShader* GetVertexShader() const;

		[[nodiscard]]
		ID3D11PixelShader* GetPixelShader() const;

		[[nodiscard]]
		ID3D11ComputeShader* GetComputeShader() const;
		
	private:

		void* mShader = nullptr;

	};
	
}

#endif
