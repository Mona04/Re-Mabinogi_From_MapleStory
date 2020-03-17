#include "Common.hlsl"

PixelTexture VS(VertexTexture input)
{
	PixelTexture output;

	output.position = mul(input.position, global_vp_ortho);
	output.uv = input.uv;

	return output;
}

Texture2D source_texture  : register(t0);
SamplerState samp         : register(s0);

float4 PS(PixelTexture input) : SV_Target
{
	float3 color = source_texture.Sample(samp, input.uv).rgb;

#if DEBUG_NORMAL
	color = Pack(color);	
#endif

#if DEBUG_VELOCITy
	color = abs(color) * 10.0f;
#endif

#if DEBUG_DEPTH
	color * float3(color.r, color.r, color.r);
#endif


	return float4(color, 1.0f);
}