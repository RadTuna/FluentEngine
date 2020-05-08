#pragma once

#ifdef API_GRAPHICS_D3D11

#include "RHI/RHIDefinition.h"
#include "RHI/Vertex.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <d3d11_1.h>
#include <vector>


#define D3D11Release(Object) \
	D3DRelease(Object); \
	Object = nullptr; \

namespace Fluent
{
	inline void D3DRelease(IUnknown* object)
	{
		if (object != nullptr)
		{
			object->Release();
		}
	}
	
	static const DXGI_FORMAT DxgiFormatMap[] =
	{
		DXGI_FORMAT_UNKNOWN,

		// R
		DXGI_FORMAT_R8_UNORM,
		DXGI_FORMAT_R16_UINT,
		DXGI_FORMAT_R16_FLOAT,
		DXGI_FORMAT_R32_UINT,
		DXGI_FORMAT_R32_FLOAT,
		DXGI_FORMAT_D32_FLOAT,
		DXGI_FORMAT_R32_TYPELESS,

		// RG
		DXGI_FORMAT_R8G8_UNORM,
		DXGI_FORMAT_R16G16_FLOAT,
		DXGI_FORMAT_R32G32_FLOAT,

		// RGB
		DXGI_FORMAT_R32G32B32_FLOAT,

		// RGBA
		DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_FORMAT_R16G16B16A16_FLOAT,
		DXGI_FORMAT_R32G32B32A32_FLOAT
	};
	inline DXGI_FORMAT ToDxgiFormat(EPixelFormat format)
	{
		const u32 index = static_cast<u32>(format);
		return DxgiFormatMap[index];
	}

	static const D3D11_PRIMITIVE_TOPOLOGY TopologyMap[] =
	{
		D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED,
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		D3D11_PRIMITIVE_TOPOLOGY_LINELIST
	};
	inline D3D11_PRIMITIVE_TOPOLOGY ToD3D11Topology(EPrimitiveTopology topology)
	{
		const u32 index = static_cast<u32>(topology);
		return TopologyMap[index];
	}

	static const D3D11_BLEND BlendMap[] =
	{
		D3D11_BLEND_ZERO,
		D3D11_BLEND_ONE,
		D3D11_BLEND_SRC_COLOR,
		D3D11_BLEND_INV_SRC_COLOR,
		D3D11_BLEND_SRC_ALPHA,
		D3D11_BLEND_INV_SRC_ALPHA
	};
	inline D3D11_BLEND ToD3D11Blend(ERenderBlend blend)
	{
		const u32 index = static_cast<u32>(blend);
		return BlendMap[index];
	}

	static const D3D11_BLEND_OP BlendOperationMap[] =
	{
		D3D11_BLEND_OP_ADD,
		D3D11_BLEND_OP_SUBTRACT,
		D3D11_BLEND_OP_REV_SUBTRACT,
		D3D11_BLEND_OP_MIN,
		D3D11_BLEND_OP_MAX
	};
	inline D3D11_BLEND_OP ToD3D11BlendOp(ERenderBlendOperation blendOp)
	{
		const u32 index = static_cast<u32>(blendOp);
		return BlendOperationMap[index];
	}

	inline void ToD3D11InputDesc(std::vector<D3D11_INPUT_ELEMENT_DESC>& outDesc, EVertexType vertexType)
	{
		const u32 vertexIndex = static_cast<u32>(vertexType);
		const u32 layoutArrayLength = InputLayoutMapsNum[vertexIndex];
		const InputLayout* generalLayout = InputLayoutMap[vertexIndex];

		outDesc.resize(layoutArrayLength);
		for (u32 index = 0; index < layoutArrayLength; ++index)
		{
			outDesc[index].SemanticName = generalLayout[index].SemanticName.c_str();
			outDesc[index].SemanticIndex = generalLayout[index].SemanticIndex;
			outDesc[index].Format = ToDxgiFormat(generalLayout[index].Format);
			outDesc[index].InputSlot = generalLayout[index].InputSlot;
			outDesc[index].AlignedByteOffset = generalLayout[index].ByteOffset;
			outDesc[index].InstanceDataStepRate = generalLayout[index].InstanceStepRate;
		}
	}

}

#endif
