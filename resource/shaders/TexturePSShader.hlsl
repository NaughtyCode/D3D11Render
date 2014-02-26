
Texture2D Diffuse : register( t0 );
SamplerState samLinear : register( s0 );

float4 PSMain( float4 Pos : SV_POSITION) : SV_Target
{
    return Diffuse.Sample( samLinear,Pos.xy);
}
