
// Common shader properties (Vertex types, samplers, constant buffers, etc...)


// Vertex types

struct VertexPos
{
    float4 Position : POSITION0;
};

struct VertexPosTex
{
    float4 Position : POSITION0;
    float2 UV : TEXCOORD0;
};

struct PixelPos
{
    float4 Position : SV_POSITION;
};

struct PixelPosTex
{
    float4 Position : SV_POSITION;
    float2 UV : TEXCOORD0;
};


// Constant buffers
 
cbuffer BufferFrame
{
    matrix gWorldMatrix;
    matrix gViewMatrix;
    matrix gProjectionMatrix;

    float gCameraNear;
    float gCameraFar;

    float2 padding;
}


// samplers

SamplerComparisonState gSamplerCompareDepth;
SamplerState gSamplerPointClamp;
SamplerState gSamplerPointWrap;
SamplerState gSamplerBilinearClamp;
SamplerState gSamplerBilinearWrap;
SamplerState gSamplerTrilinearClamp;
SamplerState gSamplerTrilinearWrap;
SamplerState gSamplerAnisotropyClamp;
SamplerState gSamplerAnisotropyWrap;

