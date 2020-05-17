
#include "Common.hlsl"

PixelPosTex mainVS(VertexPosTex input)
{
    PixelPosTex output;

    output.Position = mul(input.Position, gViewMatrix);
    output.Position = mul(output.Position, gProjectionMatrix);
	
    output.UV = input.UV;
	
    return output;
}


float4 mainPS(PixelPosTex input) : SV_TARGET
{
    return float4(1.0f, 0.0f, 0.0f, 1.0f);
}