
#ifdef API_GRAPHICS_D3D11

// Primary Include
#include "RHI/Texture2D.h"

// Engine Include
#include "RHI/Device.h"


namespace Fluent
{

	Texture2D::Texture2D(const std::shared_ptr<Device>& device, 
		u32 width, u32 height, EPixelFormat format,
		const std::vector<std::vector<u8>>& data) noexcept
		: Texture(device)
	{
		Assert(device && device->IsInitialized());
		
		mWidth = width;
		mHeight = height;
		mChannels = GetChannelCountFromFormat(format);
		mFormat = format;
		mViewFlags = static_cast<u32>(ETextureViewFlags::ShaderSampled);
		mMipLevel = static_cast<u32>(data.size());

		CreateTexture(data, 1);
	}
	
	Texture2D::Texture2D(const std::shared_ptr<Device>& device, 
		u32 width, u32 height, EPixelFormat format) noexcept
		: Texture(device)
	{
		Assert(device && device->IsInitialized());
		
		mWidth = width;
		mHeight = height;
		mChannels = GetChannelCountFromFormat(format);
		mFormat = format;
		mViewFlags = static_cast<u32>(ETextureViewFlags::ShaderSampled);
		mViewFlags |= (format == EPixelFormat::D32_Float) ?
			static_cast<u32>(ETextureViewFlags::DepthStencil) :
			static_cast<u32>(ETextureViewFlags::RenderTarget);
		mMipLevel = 1;

		CreateEmptyTexture();
	}

	Texture2D::~Texture2D() noexcept
	{
		if (mShaderResourceView)
		{
			D3D11Release(mShaderResourceView);
		}

		if (mRenderTargetView)
		{
			D3D11Release(mRenderTargetView);
		}

		if (mDepthStencilView)
		{
			D3D11Release(mDepthStencilView);
		}
	}

	bool Texture2D::CreateTexture(const std::vector<std::vector<u8>>& data, u32 arraySize)
	{
		DXGI_FORMAT renderTargetFormat = ToDxgiFormat(mFormat); // RTV = Render Target View
		DXGI_FORMAT depthStencilFormat = ToDxgiFormat(mFormat); // DSV = Depth Stencil View
		DXGI_FORMAT shaderResourceFormat = ToDxgiFormat(mFormat); // SRV = Shader Resource View
		if (mFormat == EPixelFormat::D32_Float)
		{
			renderTargetFormat = ToDxgiFormat(EPixelFormat::R32_Float_Typeless);
			depthStencilFormat = ToDxgiFormat(EPixelFormat::D32_Float);
			shaderResourceFormat = ToDxgiFormat(EPixelFormat::R32_Float);
		}

		u32 bindFlags = 0;
		bindFlags |= (mViewFlags & ETextureViewFlags::RenderTarget) ? D3D11_BIND_RENDER_TARGET : 0;
		bindFlags |= (mViewFlags & ETextureViewFlags::DepthStencil) ? D3D11_BIND_DEPTH_STENCIL : 0;
		bindFlags |= (mViewFlags & ETextureViewFlags::ShaderSampled) ? D3D11_BIND_SHADER_RESOURCE : 0;

		D3D11_TEXTURE2D_DESC texDesc = {};
		texDesc.Width = static_cast<u32>(mWidth);
		texDesc.Height = static_cast<u32>(mHeight);
		texDesc.MipLevels = static_cast<u32>(mMipLevel);
		texDesc.ArraySize = static_cast<UINT>(mTextureArraySize);
		texDesc.Format = ToDxgiFormat(mFormat);
		texDesc.SampleDesc.Count = 1;
		texDesc.SampleDesc.Quality = 0;
		texDesc.Usage = (bindFlags & D3D11_BIND_RENDER_TARGET) || (bindFlags & D3D11_BIND_DEPTH_STENCIL) ? D3D11_USAGE_DEFAULT : D3D11_USAGE_IMMUTABLE;
		texDesc.BindFlags = bindFlags;
		texDesc.MiscFlags = 0;
		texDesc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA* subResourcePtr = nullptr;
		if (!data.empty())
		{
			std::vector<D3D11_SUBRESOURCE_DATA> subResources;
			for (u32 index = 0; index < mMipLevel; ++index)
			{
				if (data[index].empty())
				{
					return false;
				}

				D3D11_SUBRESOURCE_DATA subResource = {};
				subResource.pSysMem = data[index].data();
				subResource.SysMemPitch = (mWidth >> index) * mChannels * (mBpc / 8);
				subResource.SysMemSlicePitch = 0;
				subResources.emplace_back(subResource);
			}
			subResourcePtr = subResources.data();
		}

		ID3D11Texture2D* texture = nullptr;
		const HRESULT result = mDevice->GetDevice()->CreateTexture2D(&texDesc, subResourcePtr, &texture);
		if (FAILED(result))
		{
			return false;
		}

		bool resultRTV = false;
		if (bindFlags & ETextureViewFlags::RenderTarget)
		{
			resultRTV = CreateRenderTargetView(texture, renderTargetFormat, mTextureArraySize, mDevice->GetDevice());
		}

		bool resultDSV = false;
		if (bindFlags & ETextureViewFlags::DepthStencil)
		{
			resultDSV = CreateDepthStencilView(texture, depthStencilFormat, mTextureArraySize, mDevice->GetDevice());
		}

		bool resultSRV = false;
		if (bindFlags & ETextureViewFlags::ShaderSampled)
		{
			resultSRV = CreateShaderResourceView(texture, shaderResourceFormat, mTextureArraySize, mMipLevel, mDevice->GetDevice());
		}

		D3D11Release(texture);
		return resultRTV && resultDSV && resultSRV;
	}

	bool Texture2D::CreateEmptyTexture()
	{
		std::vector<std::vector<u8>> emptyVector;
		emptyVector.reserve(0);
		return CreateTexture(emptyVector, 1);
	}

	bool D3D11Texture2D::CreateDepthStencilView(ID3D11Texture2D* texture, DXGI_FORMAT format, u32 arraySize, ID3D11Device* device)
	{
		D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
		dsvDesc.Format = format;
		dsvDesc.ViewDimension = (arraySize == 1) ? D3D11_DSV_DIMENSION_TEXTURE2D : D3D11_DSV_DIMENSION_TEXTURE2DARRAY;
		dsvDesc.Texture2DArray.MipSlice = 0;
		dsvDesc.Texture2DArray.ArraySize = 1;
		dsvDesc.Texture2DArray.FirstArraySlice = 0;

		const HRESULT result = device->CreateDepthStencilView(texture, &dsvDesc, &mDepthStencilView);
		if (FAILED(result))
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	bool D3D11Texture2D::CreateRenderTargetView(ID3D11Texture2D* texture, DXGI_FORMAT format, u32 arraySize, ID3D11Device* device)
	{
		D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
		rtvDesc.Format = format;
		rtvDesc.ViewDimension = (arraySize == 1) ? D3D11_RTV_DIMENSION_TEXTURE2D : D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
		rtvDesc.Texture2DArray.MipSlice = 0;
		rtvDesc.Texture2DArray.ArraySize = arraySize;
		rtvDesc.Texture2DArray.FirstArraySlice = 0;

		const HRESULT result = device->CreateRenderTargetView(texture, &rtvDesc, &mRenderTargetView);
		if (FAILED(result))
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	bool D3D11Texture2D::CreateShaderResourceView(ID3D11Texture2D* texture, DXGI_FORMAT format, u32 arraySize, u32 mipLevel, ID3D11Device* device)
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Format = format;
		srvDesc.ViewDimension = (arraySize == 1) ? D3D11_SRV_DIMENSION_TEXTURE2D : D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
		srvDesc.Texture2DArray.FirstArraySlice = 0;
		srvDesc.Texture2DArray.MostDetailedMip = 0;
		srvDesc.Texture2DArray.MipLevels = mipLevel;
		srvDesc.Texture2DArray.ArraySize = arraySize;

		const HRESULT result = device->CreateShaderResourceView(texture, &srvDesc, &mShaderResourceView);
		if (FAILED(result))
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	
}

#endif
