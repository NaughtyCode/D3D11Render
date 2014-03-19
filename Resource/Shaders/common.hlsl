Texture2D Diffuse : register( t0 );
SamplerState LinearSample : register( s0 );

cbuffer CBWorldViewProjectionMatrix : register( b0 )
{
    float4x4 WorldMatrix;
    float4x4 ViewMatrix;
    float4x4 ProjectionMatrix;
    float4x4 WorldViewProjectionMatrix;
};

struct VS_INPUT
{
    float4 Pos : POSITION;
    float3 normal : NORMAL;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float3 normal : NORMAL;
};

PS_INPUT VS( VS_INPUT input )
{
    PS_INPUT Output;
    Output.Pos = mul( input.Pos,WorldViewProjectionMatrix)/10.0;
    Output.normal = input.normal;
    return Output;
}

float4 PS( PS_INPUT input) : SV_Target
{
    float4 color=Diffuse.Sample( LinearSample,input.normal.xy);
    return color;
}

