
#include "Common.hlsl"

PixelPosTex mainVS(VertexPosTex input)
{
    PixelPosTex output;

    output.Position = mul(input.Position, gWorldMatrix);
    output.Position = mul(input.Position, gViewMatrix);
    output.Position = mul(input.Position, gProjectionMatrix);
    output.Position.w = 1.0f;

    output.UV = input.UV;

    return output;
}

float4 mainPS(PixelPosTex input) : SV_TARGET
{
    float4 color = float4(0.0f, 1.0f, 0.0f, 1.0f);
	return color;
}