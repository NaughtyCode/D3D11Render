Texture2D Diffuse : register( t0 );
SamplerState LinearSample : register( s0 );

cbuffer ConstantBuffer : register( b0 )
{
    float4x4 GTrans;
};

struct VS_INPUT
{
    float4 Pos : POSITION;
    float2 n : NORMAL;
};

struct PS_INPUT
{
    float3 Pos : SV_POSITION;
    float2 Tex : TEXCOORD0;
};

PS_INPUT VS( VS_INPUT input )
{
    PS_INPUT Output;
    Output.Pos = mul( input.Pos,GTrans).xyz;
    Output.Tex = input.n.xy;
    return Output;
}

float4 PS( PS_INPUT input) : SV_Target
{
    float4 color=Diffuse.Sample( LinearSample, input.Tex );
    return color;
}

