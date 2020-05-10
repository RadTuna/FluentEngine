#pragma once

#ifdef API_GRAPHICS_D3D11

// Engine Include
#include "D3D11Definition.h"


namespace Fluent
{

	class D3D11Texture2D
	{
	public:

		explicit D3D11Texture2D() = default;
		virtual ~D3D11Texture2D() = default;


		[[nodiscard]] 
		ID3D11ShaderResourceView* GetShaderResourceView() const { return mShaderResourceView; }

		[[nodiscard]]
		ID3D11RenderTargetView* GetRenderTargetView() const { return mRenderTargetView; }

		[[nodiscard]]
		ID3D11DepthStencilView* GetDepthStencilView() const { return mDepthStencilView; }

	protected:

		void CreateRenderTargetView(ID3D11Texture2D* texture, DXGI_FORMAT format, u32 arraySize, ID3D11Device* device);
		void CreateDepthStencilView(ID3D11Texture2D* texture, DXGI_FORMAT format, u32 arraySize, ID3D11Device* device);
		void CreateShaderResourceView(ID3D11Texture2D* texture, DXGI_FORMAT format, u32 arraySize, u32 mipLevel, ID3D11Device* device);

	protected:

		ID3D11Device* mDevice = nullptr;
		
		ID3D11ShaderResourceView* mShaderResourceView = nullptr;
		ID3D11RenderTargetView* mRenderTargetView = nullptr;
		ID3D11DepthStencilView* mDepthStencilView = nullptr;
		
	};

}

#endif
